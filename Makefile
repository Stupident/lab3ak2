build: main.o
	g++ -o lab3_program main.o

main.o:
	g++ -c main.cpp

clean:
	rm -f main.o lab3_program
