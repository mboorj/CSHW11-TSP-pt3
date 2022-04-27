# CSHW11-TSP-pt3


### TournamentDeme
- **constructor:** same as Deme. Creates a vector of pop_size many randomly-permuted Chromosome objects. Sets mutrate_ and generator_. Takes the sum of the fitness scores of all chromosomes, used for roulette scoring.
- **destructor:** same as Deme. Deletes each chromosome in the deme population.
- **compute_next_generation:** same as Deme. Selects pop_.size()/2 pairs of parent chromosomes with select_parent, possibly mutates them, then combines them and puts their offspring into a new population vector. Has different results because select_parent has been changed, but the method itself is still the same.
- **get_best:** same as Deme. Scans through the population vector to find the chromosome with highest fitness. 
- **select_parent:** 
