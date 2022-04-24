# include "tournament_deme.hh"

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate) :
  Deme(cities_ptr, pop_size, mut_rate) {
      // Same as other constructor
  }

Chromosome* TournamentDeme::select_parent() {
    unsigned i = 7;   // Constant exponent for 2 we will use for number of
        // Chromosomes in each tournament. Shifts sampleSize below, after it is reduced
        // if necessary so that it is no bigger than the population
    unsigned sampleSize = 1 << i;   // Constant power of 2 we will use for number of
        // Chromosomes in each tournament. Needs to be kept separately from 1 because
        // they're both used for counts
    while (sampleSize >= pop_.size()) { // If the population is too small, goes down
        // powers of two until it is of a size appropriate for the population
        --i;
        sampleSize = sampleSize >> 1;
    }
    std::vector<Chromosome*> searchable = pop_; // We need a copy of pop_ we can modify
        // to search it correctly in this way
    for(unsigned j = 0; j < sampleSize; ++j) {   // Chooses a random value from searchable
        // and moves it to the end of the vector. Repeats, not choosing from those at
        // the end, resulting in a series of non-repeated random numbers from searchable
        // being grouped together at the end of the vector
      static std::default_random_engine generator;
      std::uniform_int_distribution<int> dist(0, (searchable.size() - j - 1));
      int index = dist(generator);  // Chooses a random number in the new range
      std::swap(searchable[index], searchable[searchable.size() - j - 1]);
    }
    auto start = searchable.cbegin() + (searchable.size() - sampleSize);
    std::vector<Chromosome*> sample = std::vector<Chromosome*> ();
    while (start != searchable.cend()) {    // Copies the chosen values to a new vector
        sample.push_back(*start);
        ++start;
    }
    while (i > 0) {
        std::vector<Chromosome*> newSample = std::vector<Chromosome*> ();
        for (unsigned j = 0; j < (sample.size() - 1); (j += 2)) { // Runs it for each pair
            // until j is the last or past the last one in the sample
            Chromosome* first = sample[j];
            Chromosome* second = sample[j + 1];
            if (first->get_fitness() > second->get_fitness()) {
                newSample.push_back(first);
            } else {    // In case of a tie just pushes second
                newSample.push_back(second);
            }
        }
        sample = newSample;
        --i;
    }
    assert(sample.size() == 1);  // It should be down to one out of this selection
    return sample[0];
}
