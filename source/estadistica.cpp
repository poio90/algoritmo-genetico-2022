#include "../include/estadistica.hpp"

int Estadistica::population_size = 0;
double Estadistica::lower_bound = 0.0;
double Estadistica::upper_bound = 0.0;

//estadisticas de fitness
double Estadistica::avg_fit = 0.0;
double Estadistica::avg_init_fit = 0.0;
double Estadistica::best_init = __DBL_MAX__;
double Estadistica::best_fit = __DBL_MAX__;
double Estadistica::total_fit = 0.0;
float Estadistica::_gap = 0.0;
float Estadistica::_agap = 0.0;

//estadisticas de iteraciones
int Estadistica::best_i = 0;
int Estadistica::total_i = 0;
int Estadistica::pos_best_sol = 0;

//estadisticas de tiempo
float Estadistica::best_time = 0.0;
clock_t Estadistica::start_time = 0.0;
clock_t Estadistica::final_time = 0.0;

//estaditicas de evaluaciones
int Estadistica::total_eval = 0;
int Estadistica::best_eval = 0;

void Estadistica::set_avg_fit(){
    avg_fit = total_fit / total_eval;
}

void Estadistica::set_avg_init_fit(){
    avg_init_fit = total_fit / population_size;
}

void Estadistica::set_best_init(double fitness){
    if(fitness < best_init){
        best_init = fitness;
    }
}

void Estadistica::set_total_fit(double fitness){
    total_fit += fitness;   
}

void Estadistica::set_best_values(Individual *i, int j){
    if(i->fitness < best_fit){
        best_fit = i->fitness;
        best_i = total_i;
        get_final_time();
        best_time = get_time();
        pos_best_sol = j;
        best_eval = total_eval;
    }
    set_total_fit(i->fitness);
    set_avg_fit();
}

void Estadistica::increment_total_i(){ total_i++; }

void Estadistica::increment_total_eval(){ total_eval++; }

void Estadistica::set_population_size(int psize){ population_size = psize; }

void Estadistica::set_upper_bound(double fitness){ upper_bound = fitness; }

void Estadistica::set_lower_bound(double fitness){ lower_bound = fitness; }

void Estadistica::get_start_time(){ start_time = clock(); }

void Estadistica::get_final_time(){ final_time = clock(); }

float Estadistica::get_time(){
  return (final_time - start_time) / (float) CLOCKS_PER_SEC;
}

void Estadistica::gap(){ _gap = (best_fit - upper_bound) / upper_bound;}

void Estadistica::agap(){ _agap = (avg_fit - upper_bound) / upper_bound;}

int Estadistica::get_total_i(){ return total_i; }

int Estadistica::get_total_eval(){ return total_eval; }

double Estadistica::get_avg_fit(){ return avg_fit; }

double Estadistica::get_total_fit(){ return total_fit; }

void Estadistica::partial_sumarize(){
  ofstream info ("datos_parciales.csv");
  info << "# tamaño poblacion;#iteraciones;#evaluaciones;#;fitness promedio;mejor fitness;tiempo transcurrido" << endl;
  info << population_size << ";" << total_i << ";" << total_eval << ";" << avg_fit << ";" << best_fit << ";" << get_time() << endl;
  info.close();
}

void Estadistica::sumarize(int ID_HILO){
  ofstream info ("datos_finales.csv", ios::app);
  gap(); agap();
  info << ID_HILO << population_size << ";" << total_i << ";" << total_eval << ";" << avg_fit << ";" << best_fit << ";" << best_time << ";" << _gap << ";" << _agap << ";" << get_time() << endl;
  info.close();
}

void Estadistica::header(int ID_HILO){
  ofstream infops ("datos_finales.csv");
  infops << "#population_size;#total_iteraciones;#total_evaluaciones;#average_fit;best_fit;best_time;gap;average gap;tiempo transcurrido" << endl;
  infops.close();
}
