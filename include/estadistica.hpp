/*
    Esta clase contiene rodas las funciones relacionadas con los cálculos estadísticos del algoritmo

    sumario:
      set_avg_fit -> setea el fitness promedio
      set_avg_fit_init -> setea el fitness promedio de la inicialización de la población
      set_best_init -> setea la mejor solición al inicializar la población
      set_total_fit -> setea el fitness total de la población
      increment_total_i -> incrementa la cantidad de iteraciones
      increment_total_eval -> incrementa la cantidad de evaluaciones
      get_start_time -> setea y devuelve un timestamp al inicio
      get_final_time -> setea y devuelve un timestamp final
      set_population_size -> setea el tamaño de la población
      set_upper_bouns -> setea el limite optimo superior
      set_lower_bouns -> setea el limite optimo inferior
      set_best_value -> guarda la mejor solucion
      gap -> devuelve el porcentaje de error respecto al óptimo
      agap -> devuelve el porcentaje de error promedio respecto al óptimo
      get_total_i -> devuelve el total de iteraciones
      get_total_eval -> devuelve el total de evaluaciones
      get_avg_fit -> devuelve el fitness promedio
      get_total_fit -> devuelve el fitness total
      get_time -> devuelve el tiempo transcurrido entre inicio y fin
      sumarize -> guarda en un archivo los resultados finales de la ejecución
      partial_sumarize -> guarda en un archivo los resultados finales de cada iteracion
      header -> escribe el encabezado al comienzo del archivo
*/

#ifndef ESTADISTICA_HPP
#define ESTADISTICA_HPP

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "utils.hpp"

using namespace std; 

class Estadistica{
private:
    //estadistica de la población
    static int population_size;
    static double lower_bound;
    static double upper_bound;

    //estadisticas de fitness
    static double avg_fit;
    static double avg_init_fit;
    static double best_init;
    static double best_fit;
    static double total_fit;
    static float _gap;
    static float _agap;

    //estadisticas de iteraciones
    static int best_i;
    static int total_i;
    static int pos_best_sol;

    //estadisticas de tiempo
    static float best_time;
    static clock_t start_time;
    static clock_t final_time;
    
    //estaditicas de evaluaciones
    static int total_eval;
    static int best_eval;
public:
    static void set_avg_fit();
    static void set_avg_init_fit();
    static void set_best_init(double);
    static void set_total_fit(double);
    static void increment_total_i();
    static void get_final_time();
    static void get_start_time();
    static void increment_total_eval();
    static void set_population_size(int);
    static void set_upper_bound(double);
    static void set_lower_bound(double);
    static void set_best_values(Individual*, int);
    static void gap();
    static void agap();
    static int get_total_i();
    static int get_total_eval();
    static double get_avg_fit();
    static double get_total_fit();
    static float get_time();
    static void partial_sumarize();
    static void sumarize(int);
    static void header(int);
    void set_nombre_archivo(string);
};

#endif
