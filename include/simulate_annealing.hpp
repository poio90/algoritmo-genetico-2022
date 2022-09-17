#ifndef SIMULATE_ANNEALING_H
#define SIMULATE_ANNEALING_H

#include <cmath>
#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace std;

class SimulateAneadling
{
private:
    int resultado_previo;
    // int m_last_res;
    double T0;
    double T_final;
    double time_step;
    int epoch;

public:
    /**
     * @brief Construct a new Simulate Aneadling object
     *
     * @param T0
     * @param T_final
     * @param time_step
     */
    SimulateAneadling(double T0, double T_minimo, double time_step);

    //~SimulateAneadling();
    int revertir_cambio();

    int hacer_cambios_y_calcuar_resultado();

    double get_transicion_probabilidad(int E1, int E2, double T);

    double enfriamiento(double T0, double T_actual, int iter_actual);

    /**
     * @brief Aceptar la solución de acuerdo a la probabilidad
     *
     *
     * @param E1
     * @param E2
     * @param T
     * @return int
     */
    int cambio_con_probabilodad(int E1, int E2, double T);

    void simulate();
};

#endif