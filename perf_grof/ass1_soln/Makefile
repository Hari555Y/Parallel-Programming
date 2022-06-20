CC=g++ -fopenmp
#g++ -std=c++11 -O2 -mavx2 -c classify.cpp 
CFLAGS=-std=c++11 -O2

sources=main.cpp classify.cpp
objects=$(sources:.cpp=.o)

classify:$(objects)
	$(CC) $(CFLAGS) -g -pg $^ -o $@

run: classify
	./classify rfile dfile 1009072 4 3

valgrind: classify
	valgrind ./classify rfile dfile 1009072 4 3
	
gprof: classify 
	gprof ./classify gmon.out > gprof_report.out

#classify.o: classify.h
#	touch classify.o
#	$(CC) $(CFLAGS) -c $<
#main.o: classify.h
#	$(CC) $(CFLAGS) -c $<

%.o: %.cpp classify.h
	$(CC) $(CFLAGS) -c -g -pg $<

