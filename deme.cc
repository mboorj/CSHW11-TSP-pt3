/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
{
  uint i = 0;
  while (i < pop_size){
    Chromosome* c = new Chromosome(cities_ptr); // randomly ordered by constructor
    pop_.push_back(c);
    i++;
  }

  mut_rate_ = mut_rate;
  std::random_device rd;
  generator_.seed(rd());
  std::default_random_engine generator_;

  pop_fit_ = sum_fitness();
}

// Clean up as necessary
Deme::~Deme()
{
  for (auto c : pop_) {  // Deletes all the chromosomes being held on the stack
      delete c;
  }
}

// Calculate the roulette selection score of a given chromosome in the population
double Deme::roulette_score(Chromosome* c){
  return (c->get_fitness()/pop_fit_);
}

// Take the total fitness of the population, for roulette
double Deme::sum_fitness(){
  double sum = 0;
  for (auto c : pop_){
    sum += c->get_fitness();
  }
  return sum;
}



// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
  // Add your implementation here
  std::vector<Chromosome*> new_pop;
  uint i = 0;

  while (i < pop_.size()/2){
    auto parent1 = select_parent();
    auto parent2 = select_parent();
    while (parent2 == parent1){
      parent2 = select_parent();
    }

    static std::uniform_real_distribution<double> dis(0.0, 1.0);
    const double mut_chance1 = dis(generator_); // make a random number [0,1]
    if (mut_chance1 <= mut_rate_){
      parent1->mutate();
    }
    const double mut_chance2 = dis(generator_); // make a random number [0,1]
    if (mut_chance2 <= mut_rate_){
      parent2-> mutate();
    }
    auto offspring = parent1->recombine(parent2);
    new_pop.push_back(offspring.first);
    new_pop.push_back(offspring.second);

    i++;
  }
  for (auto c : pop_) {   //Make sure the old population is properly deleted
      delete c;
  }
  pop_ = new_pop; // ignore parent generation, use only child generation
  pop_fit_ = sum_fitness(); // find new total fitness score
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  assert(pop_.size());  // Throws an error if there are no elements to look at
  Chromosome* best = pop_[0];
  for (auto c : pop_){
    if (c->get_fitness() > best->get_fitness()){
      best = c;
    }
  }
  return best;
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
  static std::uniform_real_distribution<double> dis(0.0, 1.0);
  double prob = dis(generator_);// make a random number 0 to 1. All of the
    // roulette_scores of the elements should add up to 1, so if we just count
    // through them until we hit the one that this value falls in we'll have
    // accurately chosen
  assert((prob >= 0) && (prob <= 1));   // Makes sure it's actually within the correct
    // range
  int i = -1;   // Start at -1 instead of 0 because we're going to increment it
    // immediately
  do {
      ++i;
      assert((long unsigned int)(i) < pop_.size()); // Makes sure we're not
        // going out of range, because that would mean something is wrong here
      prob -= roulette_score(pop_[i]);  // Subtract the current score from the prob.
        // As this goes on, prob will drop to or below 0 when you hit the correct chromosome
  } while ((prob > 0) && ((long unsigned int)(i + 1) < pop_.size()));  // That second clause
    // is there because floating points can be a little inaccurate and we might be super
    // close to 0, but not quite there, resulting in us looking for another element when
    // there isn't one
  return pop_[i];
}
