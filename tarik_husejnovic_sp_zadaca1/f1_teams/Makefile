all: main.o f1.o f1_teams.o
	clang++ main.o f1.o f1_teams.o -o program

main.o: main.cpp
	clang++ -c main.cpp

f1.o: f1.cpp
	clang++ -c f1.cpp

f1_teams.o: f1_teams.cpp
	clang++ -c f1_teams.cpp

clean:
	rm -rf *.o program
