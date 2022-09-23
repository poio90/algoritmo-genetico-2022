#ifndef GA_HPP
#define GA_HPP

#include "problem.hpp"
#include "selector.hpp"
#include "crossover.hpp"
#include "mutator.hpp"
#include "replacer.hpp"

class GA {
  
  private:
    float pcrossover;
    float pmutation;
    int id_thread;

    Mutator *m;
    Selector *s;
    Replacer *r;
    Crossover *c;

public:
  GA(string);
  void run(int ID_THREAD, Population *parents, Population *offprings, Problem *p);
};


#endif