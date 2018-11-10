CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors
assignment = hw6
lib=$(assignment).a

$(lib): Alpha.o PGM.o Image.o
	$(AR) -rcs $@ $?

Alpha.o: Alpha.h Alpha.cc
	$(CXX) $(CXXFLAGS) -c Alpha.cc
PGM.o: PGM.h PGM.cc
	$(CXX) $(CXXFLAGS) -c PGM.cc
Image.o: Image.h Image.cc
	$(CXX) $(CXXFLAGS) -c Image.cc
tar:
	tar -cv $(MAKEFILE_LIST) *.cc *.h >$(assignment).tar
test: $(lib)
	$(CXX) $(CXXFLAGS) test.cc $(lib)
	./a.out
clean:
	rm -f $(assignment) $(assignment).{a,tar} *.o *.gch a.out
