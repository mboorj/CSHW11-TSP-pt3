# CSHW11-TSP-pt3
This project is a collaboration between Tiago Beck and Mollie Boor. To build the climb chromosome portion, use ```make tsp_climb```. To build the tournament deme portion, use ```make tourn```.

### ClimbChromosome
All methods except clone and mutate are the same as Chromosome.
- **mutate:** randomly selects an index within the chromosome's permutation to center the mutation around. Tests the results of swapping the city with the city at index-1, swapping with the city at index+1, and keeping the city in place. Sets the chromosome's order to the most fit of the three options.
- **clone:** returns a new ClimbChromosome instead of a standard Chromosome.

### TournamentDeme
While running tourn, Tiago experienced stack smash errors many iterations into the run. We worked with tutors but were not able to replicate the error on any computer except his.
- **constructor:** almost the same as Deme. Creates a vector of pop_size many randomly-permuted Chromosome objects. Sets mutrate_ and generator_. Takes the sum of the fitness scores of all chromosomes, used for roulette scoring. Also calculates the power of two used in select_parent and stores it as a data member.
- **destructor:** same as Deme. Deletes each chromosome in the deme population.
- **compute_next_generation:** same as Deme. Selects pop_.size()/2 pairs of parent chromosomes with select_parent, possibly mutates them, then combines them and puts their offspring into a new population vector. Has different results because select_parent has been changed, but the method itself is still the same.
- **get_best:** same as Deme. Scans through the population vector to find the chromosome with highest fitness. 
- **select_parent:** randomly chooses a pool of Chromosomes from the population then pits each of them against each other in pairs. The better of each pair is put into a new pair, and the better of that into a new one and so on until there is only one pair left, and the better of that pair is selected as the parent.
