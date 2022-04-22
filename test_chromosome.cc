# include "chromosome.hh"

int main () {
    std::vector<Cities::coord_t> vect = std::vector<Cities::coord_t> ();
    vect.push_back(std::make_pair(2, 4));
    vect.push_back(std::make_pair(30, 1));
    vect.push_back(std::make_pair(22, 22));
    const Cities* cities = new Cities(vect);

    Chromosome chrom = Chromosome(cities);
    Chromosome* cloneChrom = chrom.clone();

    return 0;
}
