#include "../include/mutator.hpp"

Mutator::Mutator(int n){
  switch(n){
    case 0: operatorm = &Mutator::invert;
      break;
    case 1: operatorm = &Mutator::insert;
      break;
    case 2: operatorm = &Mutator::interchange;
      break;
    default: operatorm = &Mutator::invert;
      break;
  }
}

void Mutator::mutate(float pmutate, Population *offprings){    
    Utils u;    
    int size = offprings->individual[0].solution.size;
    double r = 0.0;
    int i=0, mutpoint1=0, mutpoint2=0;

    while(i<offprings->size){
      r = u.randd(0,1);
      if(r<pmutate){ 
        mutpoint1 = rand() % size;

        do{
            mutpoint2 =  rand() % size;
        }while(mutpoint2 == mutpoint1);

        if(mutpoint1 > mutpoint2){
            int aux = mutpoint2;
            mutpoint2 = mutpoint1;
            mutpoint1 = aux;
        }

        (this->*operatorm)(&(offprings->individual[i].solution.chromosome[mutpoint1]), &(offprings->individual[i].solution.chromosome[mutpoint2]));            

        offprings->individual[i].updated = 0;
      }
      i++;
    }
}

void Mutator::insert(int *pa, int *pb){
  int *indice;
  indice = pb - 1;
  while (pa != indice){
    interchange(indice, pb);
    pb = indice;
    indice--;
  }
}

void Mutator::interchange (int *pa, int *pb){
  int aux = 0;
  aux = *pa;
  *pa = *pb;
  *pb = aux;
}

void Mutator::invert(int *pa, int *pb){
  while(pa < pb){
    interchange(pa, pb);
    pa++;
    pb--;
  }
}
