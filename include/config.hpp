/*
  Esta clase contiene las funciones necesarias para cargar la configuracion

  summario:
    read() -> lee los parámetros de configuración en el archivo /config/ga.config e inicializa las variables
*/
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Configuration{
private:
public:
    int epoch;
    int mu;
    int lambda;
    int generator;
    int pselection;
    int npreplacement;
    int npselection;
    int mutation;
    float pmutation;
    int crossover;
    float pcrossover;
    void read(char*);
};

#endif
