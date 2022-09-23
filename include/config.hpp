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
#include <string>

using namespace std;

class Configuration{
private:
public:
    Configuration();
    int epoch;
    int mu; //cantidad de padres
    int lambda;//cantidad de hijos
    int generator;
    int pselection;
    int npreplacement;
    int npselection;
    int mutation;
    float pmutation;
    int crossover;
    float pcrossover;
    void read(string);
    //NUEVOS PARAMETROS y funciones
    void read_ga(string);
    void read_sa(string);
    int intervalo_migraciones;
    int cantidad_inmigrantes;
    double probabilidad_quedarse_con_imigrante_malo;
    string FSSP_instance;
    double T0;
    double T_final; 
    double alpha;
    double time_step; 
};

#endif
