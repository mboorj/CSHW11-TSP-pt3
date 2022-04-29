#pragma once

#include "deme.hh"

// A class that inherits from Deme but changes its method of parent selection
class TournamentDeme : public Deme {
  public:
      // Generate a TournamentDeme of the specified size with all-random chromosomes.
      // Also receives a mutation rate in the range [0-1].
      TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);
  protected:
      // Select a chromosome in the population based on fitness by pitting
      // chromosomes against each other and choosing the better, and
      // return a pointer to that chromosome.
      virtual Chromosome* select_parent();

      // Holds onto the exponent for the greatest power of 2 that is smaller
      // than the pop_ size
      unsigned pow2;
};
