CXXFLAGS = -Wall -Werror -std=c++14
CONVERT_OBJS = units.o convert.o
HW3TESTUNITS_OBJS = units.o testbase.o hw3testunits.o

all: convert hw3testunits

convert: $(CONVERT_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

hw3testunits: $(HW3TESTUNITS_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test: all
	./hw3testunits

doc:
	doxygen

clean:
	rm -f convert hw3testunits *.o *~ -r docs

.PHONY: all clean test doc
