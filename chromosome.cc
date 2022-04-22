/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>
#include <numeric>

#include "chromosome.hh"


static std::random_device rd;  // Static so we don't initialize every time
static std::default_random_engine g(rd());
//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size())),
    generator_(g())
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void
Chromosome::mutate()
{
  if (order_.size() > 1){
    int ind1 = generator_() % (order_.size()); // random number 0 to size -1
    int ind2 = generator_() % (order_.size());
    while (ind1==ind2){
      ind2 = generator_() % (order_.size());
    }
    std::swap(order_[ind1], order_[ind2]);
  }

  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
  assert(is_valid());
  assert(other->is_valid());

  unsigned index1;  // Define the variables that hold the range so that they
    // remain outside the while loop
  unsigned index2;
  index1 = generator_() % (order_.size()); // generates the range
  index2 = generator_() % (order_.size());
  if (index1 >= index2){
    auto temp = index1;
    index1=index2;
    index2=temp;
  }
  const Chromosome* thisPtr = this;
  Chromosome* child1 = create_crossover_child(thisPtr, other, index1, index2);
  Chromosome* child2 = create_crossover_child(other, thisPtr, index1, index2);
  return std::make_pair(child1, child2);
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        j++;
        assert(j < p2->order_.size());
      }
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  double distance = cities_ptr_->total_path_distance(order_);    // The distance of the current
    // ordering
  return 1.0 / distance;
}

// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
bool
Chromosome::is_valid() const
{
  auto sorted = order_;
  std::sort(sorted.begin(), sorted.end());
  auto has_repeat = std::adjacent_find(sorted.begin(), sorted.end());
  if (has_repeat != sorted.end()){
    return false;
  }
  auto greatest = sorted[sorted.size()-1]; // last, and greatest, element
  if (greatest >= order_.size()){
    return false;
  }
  return true;
}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  auto loc_found = std::find(&order_[begin], &order_[end], value);
  if (loc_found == &order_[end]){
    return false;
  }
  return true;
}
