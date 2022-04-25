CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -O0 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  tsp

tsp: tsp.o chromosome.o deme.o cities.o
	$(CXX) $(LDFLAGS) -o $@ $^

tsp_climb: tsp_climb.o climb_chromosome.o deme_climb.o cities.o chromosome.o
	$(CXX) $(LDFLAGS) -o $@ $^

tourn: tourntsp.o tournament_deme.o chromosome.o deme.o cities.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_chromosome: test_chromosome.o chromosome.o cities.o
	$(CXX) $(LDFLAGS) -o $@ $^


%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o tsp

copy:
	scp * patty:ga
