CXXFLAGS = -std=c++14 -Wall

all : test-regex

test-regex : engine.o regex.o test-regex.o testbase.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean :
	rm -f test-regex *.o *~

.PHONY : all clean

