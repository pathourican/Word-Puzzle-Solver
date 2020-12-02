# Patrick Hourican
# pjh4as

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-Wall -O2 #Enable all warnings
DEBUG=-g

wordPuzzle: wordPuzzle.o hashTable.o timer.o
		$(CXX) $(DEBUG) wordPuzzle.o hashTable.o timer.o -o a.out

wordPuzzle.o: wordPuzzle.cpp

hashTable.o: hashTable.cpp hashTable.h

timer.o: timer.cpp timer.h

.PHONY: clean
clean:
	-rm -f *.o a.out
