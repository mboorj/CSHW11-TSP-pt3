/*
 *  Changes mutation implementation from original Chromosome class
 */


#pragma once

#include "cities.hh"
#include "chromosome.hh"
#include <random>

class ClimbChromosome : public Chromosome{

 public:

  ClimbChromosome(const Cities* cities_ptr) : Chromosome(cities_ptr){}
  
  virtual ~ClimbChromosome() = default;

  // Test two mutations within a neighbood of options, use the fittest
  virtual void mutate();

  // Makes sure reproduction methods return the correct kind of chromosome
  virtual Chromosome* clone() const
  {
    return new ClimbChromosome(cities_ptr_);
  }

  // Get a writeable
  //virtual Cities::permutation_t get_order();


};
