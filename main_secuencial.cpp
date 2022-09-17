#include <omp.h>
#include <random>
#include <stdio.h>
#include "include/config.hpp"
#include "include/problem.hpp"
#include "include/selector.hpp"
#include "include/crossover.hpp"
#include "include/mutator.hpp"
#include "include/replacer.hpp"

const int NUM_HILOS = omp_get_num_procs();

int main(int argc, char *argv[])
{

    // leemos la configuracion del archivo  ga.config
    Configuration cfg;
    cfg.read("./config/ga.config");

    omp_set_num_threads(NUM_HILOS);

#pragma omp parallel firstprivate(cfg)
    {
        const int ID_THREAD = omp_get_thread_num();
        // poner semilla aleatoria para cada thread individualmente
        random_device rng;
        srand(rng());

        // Creamos estadistica
        Estadistica estadistica;
        
        // Código acá


        #pragma omp critical
        {
            estadistica.set_nombre_archivo("datosFinales.csv");
            estadistica.header(ID_THREAD);
            estadistica.sumarize(ID_THREAD);
        }
    }

    // printf("================================================================== \n");
}
