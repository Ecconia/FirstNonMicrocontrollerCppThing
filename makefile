all: Test;

clean:
	rm -f *.o Test
	rm -rf bin/*

Test: bin/IOHelper.o bin/Test.o
	g++ -o Test bin/Test.o bin/IOHelper.o

bin/Test.o: bin/IOHelper.o src/Test.cpp
	g++ -c -o bin/Test.o src/Test.cpp

bin/IOHelper.o: src/IOHelper.h src/IOHelper.cpp
	g++ -c -o bin/IOHelper.o src/IOHelper.cpp