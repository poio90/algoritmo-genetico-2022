#include "../include/simulate_annealing.hpp"

SimulateAneadling::SimulateAneadling(double T0, double T_final, double time_step) : T0(T0), T_final(T_final), time_step(time_step), resultado_previo(99999)
{
}

//~SimulateAneadling();
int SimulateAneadling::revertir_cambio()
{
    return resultado_previo;
}

int SimulateAneadling::hacer_cambios_y_calcuar_resultado()
{
    // return cambios;
    // obtenemos vecinos aleatorios del estado actual
}

double SimulateAneadling::get_transicion_probabilidad(int E1, int E2, double T)
{
    // double r = exp((E1 - E2) / T);
    // // cout << E1 << "----" << E2 << " = " << E1 - E2 << " p= " << r << endl;
    // return r;
    return exp((E1 - E2) / T);
}

double SimulateAneadling::enfriamiento(double T0, double T_actual, int iter_actual)
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
     *   * Para controlar el número de iteraciones (Cauchy modificado): Tk+1 = Tk / (1 + b*Tk)
     *   * Para ejecutar exactamente M iteraciones --> beta = (To – Tf) / (M*To*Tf)
     *   * https://sci2s.ugr.es/sites/default/files/files/Teaching/GraduatesCourses/Metaheuristicas/Tema05-Metodos%20basados%20en%20trayectorias-18-19.pdf
     */
    int n = 0; // Definir este n por el número de thread
    double r = T_actual;
    switch (n)
    {
    case 0:
        // Criterio de Boltzmann:
        r = T0 / (1 + log(iter_actual));
        break;
    case 1:
        // Esquema de Cauchy
        r = T0 / (1 + iter_actual);
        break;
    case 2:
        // Cauchy modificado
        r = T_actual / (1 + ((T0 - T_final) / (iter_actual * T0 * T_final)) * T_actual);
        break;
    default:
        // Descenso geométrico
        r = T_actual * 0.99;
        break;
    }
    return r;
}

/**
 * @brief Aceptar la solución de acuerdo a la probabilidad
 *
 *
 * @param E1
 * @param E2
 * @param T
 * @return int
 */
int SimulateAneadling::cambio_con_probabilodad(int E1, int E2, double T)
{
    // Si la nueva solucion no es mejor, aceptarla con una probabilidad de e^(-costo/temp)
    int E = E2;
    if (E2 < E1)
    {
        double p = get_transicion_probabilidad(E1, E2, T); // probabilidad para aceptar solución
        double v = (double)rand() / (RAND_MAX);            // Números aleatorios entre 0 y 1

        if (p > 0 || p < 1)
        {
            cout << " v is " << v << " p is " << p << endl;
            if (v >= p)
            {
                E = revertir_cambio();
            }
        }
    }
    return E;
}

void SimulateAneadling::simulate()
{
    double time = 1.0;
    double T = T0;
    int resultado = 0;

    while (T > T_final)
    {
        for (int i = 0; i < epoch; i++)
        {
            // cout << time << endl;
            resultado = hacer_cambios_y_calcuar_resultado();
            if (resultado > resultado_previo)
                resultado = cambio_con_probabilodad(resultado_previo, resultado, T);

            resultado_previo = resultado;
            T = enfriamiento(T0, T, i);
            time = time + time_step;
            // cout << "\n";
        }
    }
};
