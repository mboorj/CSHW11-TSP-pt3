# include "tournament_deme.hh"

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate) :
  Deme(cities_ptr, pop_size, mut_rate) {
      // Same as other constructor, + the following
      pow2 = 0;
      while ((long unsigned)(1 << (pow2 + 1)) < pop_.size()) {
          ++pow2;
      } // finds the greatest power of 2 that is smaller than the pop_ size and
      // stores the exponent
      std::cout << "Pow2: " << pow2 << ", Ex: " << (1 << pow2) << "\n";
  }

Chromosome* TournamentDeme::select_parent() {
    unsigned sampleSize = 1 << pow2;   // Constant power of 2 we will use for number of
        // Chromosomes in each tournament. Needs to be kept separately from pow2 because
        // they're both used for counts
    std::vector<Chromosome*> searchable = pop_; // We need a copy of pop_ we can modify
        // to search it correctly in this way
    for(unsigned i = 0; i < sampleSize; ++i) {   // Chooses a random value from searchable
        // and moves it to the end of the vector. Repeats, not choosing from those at
        // the end, resulting in a series of non-repeated random numbers from searchable
        // being grouped together at the end of the vector
      static std::default_random_engine generator;
      std::uniform_int_distribution<int> dist(0, (searchable.size() - i - 1));
      int index = dist(generator);  // Chooses a random number in the new range
      std::swap(searchable[index], searchable[searchable.size() - i - 1]);
    }
    auto start = searchable.cbegin() + (searchable.size() - sampleSize);
    std::vector<Chromosome*> sample = std::vector<Chromosome*> ();
    while (start != searchable.cend()) {    // Copies the chosen values to a new vector
        sample.push_back(*start);
        ++start;
    }
    for (unsigned i = pow2; i > 0; --i) {
        std::vector<Chromosome*> newSample = std::vector<Chromosome*> ();
        for (unsigned j = 0; j < sample.size(); (j += 2)) { // Runs it for each pair
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
    }
    assert(sample.size() == 1);  // It should be down to one out of this selection
    return sample[0];
}
