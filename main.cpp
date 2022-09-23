#include <omp.h>
#include <random>
#include <stdio.h>
#include "include/config.hpp"
#include "include/problem.hpp"
#include "include/selector.hpp"
#include "include/crossover.hpp"
#include "include/mutator.hpp"
#include "include/replacer.hpp"
#include "include/estadistica.hpp"
#include "include/Servicio_inmigracion.hpp"
#include "include/simulate_annealing.hpp"

#include "include/ga.hpp"

// const int NUM_HILOS = omp_get_num_procs();
const int NUM_HILOS = 4;

int main(int argc, char *argv[])
{
    // leemos la configuracion del archivo  ga.config
    Configuration cfg_global;
    cfg_global.read("./config/config.config");

    GA *ga1 = new GA("./config/ga1.config");
    GA *ga2 = new GA("./config/ga2.config");
    SimulateAnnealing *sa1 = new SimulateAnnealing("./config/sa1.config");
    SimulateAnnealing *sa2 = new SimulateAnnealing("./config/sa2.config");

    //punteros para referenciar servicio de inmigrante entre hilos
    Servicio_inmigracion *p_servicios[NUM_HILOS];

#pragma omp parallel firstprivate(cfg_global, ga1, ga2, sa1, sa2) num_threads(NUM_HILOS)
    {
        cout << "intervalo_migraciones" << cfg_global.intervalo_migraciones << endl;
        const int ID_THREAD = omp_get_thread_num();
        // poner semilla aleatoria para cada thread individualmente
        random_device rng;
        srand(rng());

        // Creamos estadistica
        Estadistica estadistica;

        // inicializamos el problema
        Problem p(estadistica);
        p.load(cfg_global.FSSP_instance);

        int isla_a_emigrar = (ID_THREAD + 1) % NUM_HILOS;

        Servicio_inmigracion *servicio;

        Utils u;
        Population *parents = (Population *)malloc(sizeof(Population));
        Population *offprings = (Population *)malloc(sizeof(Population));
        servicio = new Servicio_inmigracion(p, cfg_global.cantidad_inmigrantes, cfg_global.probabilidad_quedarse_con_imigrante_malo);
        p_servicios[ID_THREAD]= servicio;

        // Se divide por la cantidad de hilos, así si la población es 100, y se tienen
        // 4 hilos, cada isla tendra 25 individuos como población
        p.initialize_parents((int)(cfg_global.mu / NUM_HILOS), parents);
        p.initialize_population((int)(cfg_global.lambda / NUM_HILOS), offprings);

        estadistica.set_start_time();
        int i = 0;
        do
        {
            switch (ID_THREAD)
            {
            case 0:
                //cout << "AG: " << omp_get_thread_num() << endl;
                ga1->run(ID_THREAD,parents,offprings,&p);
                break;
            case 1:
                sa1->simulate(ID_THREAD, parents, &p);
                u.copy_population(parents,offprings);
                break;
            case 2:
                //cout << "AG: " << omp_get_thread_num() << endl;
                ga2->run(ID_THREAD,parents,offprings,&p);
                break;
            case 3:
                sa2->simulate(ID_THREAD, parents, &p);
                u.copy_population(parents,offprings);
                break;
            default:
                break;
            }
            i++;
            // es hora de migrar
            if (i % cfg_global.intervalo_migraciones == 0)
            {
                servicio->copiar_mejores(offprings);
                // Sincroniza todos los subprocesos de un equipo
                #pragma omp barrier
                p_servicios[isla_a_emigrar]->eliminar_peores_y_migrar(offprings);
            }
            estadistica.increment_total_i();
        } while (i < cfg_global.epoch);
        estadistica.set_final_time();

        #pragma omp critical
        {
            estadistica.set_nombre_archivo("datosFinales.csv");
            estadistica.header(ID_THREAD);
            estadistica.sumarize(ID_THREAD);
        }
        delete servicio;
        free(parents);
        free(offprings);
    }
    printf("================================================================== \n");
    return EXIT_SUCCESS;
}
