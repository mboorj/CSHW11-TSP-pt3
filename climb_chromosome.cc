/*
 *  Implementation of new mutation for ClimbChromosome class
 */

#include "climb_chromosome.hh"

void ClimbChromosome::mutate(){
  uint ind = generator_() % (order_.size()); // random number 0 to size -1
  auto testSave = order_;
  auto testBehind = order_; // swap random point with one behind
  auto testAhead = order_; // swap random point with one in front

  if (ind == 0){
    std::swap(testBehind[ind], testBehind[testBehind.size()-1]); // swap first and last if needed
    std::swap(testAhead[ind], testAhead[ind+1]); // swap ind and ind+1 for test 2
  } else if (ind == order_.size()-1){
    std::swap(testBehind[ind], testBehind[ind-1]); // swap ind and ind-1 for test 1
    std::swap(testAhead[ind], testAhead[0]); // swap last and first if needed
  } else {
    std::swap(testBehind[ind], testBehind[ind-1]); // swap ind and ind-1 for test 1
    std::swap(testAhead[ind], testAhead[ind+1]); // swap ind and ind+1 for test 2
  }

  auto ogFit = get_fitness();
  order_ = testBehind;
  auto behindFit = get_fitness();
  order_ = testAhead;
  auto aheadFit = get_fitness();

  if ((ogFit >= behindFit) && (ogFit >= aheadFit)){
    order_ = testSave;
  }
  if ((behindFit >= ogFit) && (behindFit >= aheadFit)){
    order_ = testBehind;
  } // don't need to test for ahead, if it's the best, it's already set to order

  //if((t1Fit >= t2Fit) && (t1Fit >= ogFit)){
  //  this = testBehind;
  //}
  //if ((t2Fit >= t1Fit) && (t2Fit >= ogFit)){
  //  this = testAhead;
  //}

  assert(is_valid());
}
