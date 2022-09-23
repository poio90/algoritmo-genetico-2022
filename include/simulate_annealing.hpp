#ifndef SIMULATE_ANNEALING_H
#define SIMULATE_ANNEALING_H

#include <cmath>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include "problem.hpp"

using namespace std;

class SimulateAnnealing
{
private:
    Utils u;
    // int m_last_res;
    double T0;
    double T_final;
    double time_step;
    double alpha;
    int op_unario;
    float pmutatation;

public:
    /**
     * @brief Construct a new Simulate Aneadling object
     *
     * @param T0
     * @param T_final
     * @param time_step
     */
    SimulateAnnealing(string file);

    //~SimulateAnnealing();

    double get_transicion_probabilidad(double E1, double E2, double T);

    double enfriamiento(int ID_THREAD, double T0, double T_actual, double time, int iter_actual);

    void simulate(int, Population *, Problem *);
};

#endif