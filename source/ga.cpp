#include "../include/ga.hpp"

GA::GA(string file)
{
  Configuration cfg;
  cfg.read_ga(file);
  this->pcrossover = cfg.pcrossover;
  this->pmutation = cfg.pmutation;
  this->s = new Selector(cfg.pselection);
  this->c = new Crossover(cfg.crossover);
  this->r = new Replacer(cfg.npreplacement, cfg.npselection);
};

void GA::run(int ID_THREAD, Population *parents, Population *offprings, Problem *p)
{
  Mutator m(ID_THREAD);
  s->select(parents, offprings);
  c->crossover(this->pcrossover, offprings);
  m.mutate(this->pmutation, offprings);
  p->evaluate_population(offprings);
  r->replace(parents, offprings, p);
}
