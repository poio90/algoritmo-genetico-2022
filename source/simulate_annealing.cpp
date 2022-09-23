#include "../include/config.hpp"
#include "../include/mutator.hpp"
#include "../include/simulate_annealing.hpp"

SimulateAnnealing::SimulateAnnealing(string file)
{
    Configuration cfg;
    cfg.read_sa(file);
    this->T0 = cfg.T0;
    this->T_final = cfg.T_final;
    this->time_step = cfg.time_step;
    this->op_unario = cfg.mutation;
    this->alpha = cfg.alpha;
    this->pmutatation = cfg.pmutation;
}

//~SimulateAneadling();
double SimulateAnnealing::get_transicion_probabilidad(double E1, double E2, double T)
{
    return exp((E1 - E2) / T);
}

double SimulateAnnealing::enfriamiento(int ID_THREAD, double T0, double T_actual, double time, int iter_actual)
{
    /**
     * @brief
     * Mecanismo de enfriamiento
     *   Existen varios mecanismos de enfriamiento:
     *  * Enfriamiento basado en sucesivas temperaturas descendentes fijadas por el usuario
     *   * Enfriamiento con descenso constante de temperatura
     *   * Descenso geométrico: T(k+1) = alpha*Tk
     *      * k = nº iteración actual, alpha constante cercana a 1 (usualmente, alpha in [0.8, 0.99])
     *   * Criterio de Boltzmann: Tk = T0 / (1 + log(k))
     *   * Esquema de Cauchy: Tk = T0 / (1 + k)
     *   * Para controlar el número de iteraciones (Cauchy modificado): Tk+1 = Tk / (1 + beta*Tk)
     *   * Para ejecutar exactamente M iteraciones --> beta = (To – Tf) / (M*To*Tf)
     *   * https://sci2s.ugr.es/sites/default/files/files/Teaching/GraduatesCourses/Metaheuristicas/Tema05-Metodos%20basados%20en%20trayectorias-18-19.pdf
     */
    double r = T_actual;
    int M = 40; // M iteraciones elegidas al azar, podría ser el valor de T0 inicial de la config
    switch (ID_THREAD)
    {
    // case 0:
    //     Criterio de Boltzmann -> demasiado muy lenta
    //     cout << "Criterio de Boltzmann" << endl;
    //     r = T0 / (1 + log(iter_actual));
    //     break;
    case 0:
        // definido por el usuario
        r = T0 * pow(alpha, time);
        break;
    case 1:
        // Esquema de Cauchy
        r = T0 / (1 + iter_actual);
        break;
    case 2:
        // Cauchy modificado(hace exactamente el número M que se especifique)
        r = T_actual / (1 + ((T0 - this->T_final) / (M * T0 * this->T_final)) * T_actual);
        break;
    default:
        // Descenso geométrico
        r = T_actual * alpha;
        break;
    }
    return r;
}

void SimulateAnnealing::simulate(int ID_THREAD, Population *estado_actual, Problem *p)
{
    Mutator m(ID_THREAD);
    Population *estado_inicial = (Population *)malloc(sizeof(Population));
    int i = 0;
    double time = 1.0;
    double probabilidad, T = T0;
    p->initialize_parents((int)estado_actual->size, estado_inicial);
    this->u.copy_population(estado_actual, estado_inicial);

    while (T > T_final)
    {
        m.mutate(this->pmutatation, estado_actual);
        p->evaluate_population(estado_actual);

        for (int j = 0; j < estado_actual->size; j++)
        {
            if (estado_actual->individual[j].fitness < estado_inicial->individual[j].fitness)
            {
                this->u.copy_individual(&(estado_actual->individual[j]), &(estado_inicial->individual[j]));
            }
            else
            {
                probabilidad = get_transicion_probabilidad(estado_inicial->individual[j].fitness, estado_actual->individual[j].fitness, T);
                if (probabilidad > 0 && probabilidad < 1)
                {
                    if (this->u.randd(0, 1) <= probabilidad)
                    {
                        this->u.copy_individual(&(estado_actual->individual[j]), &(estado_inicial->individual[j]));
                    }
                }
            }
        }
        i++;
        T = enfriamiento(ID_THREAD, T0, T, time, i);
        time = time + time_step;
    }
    free(estado_inicial);
};
