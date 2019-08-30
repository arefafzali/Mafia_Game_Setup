COMPILER = g++
a.out: main.o god.o room.o roles.o headers.o
	${COMPILER} main.o god.o room.o roles.o headers.o

main.o: main.cpp god.h room.h
	${COMPILER} -c main.cpp

god.o: god.cpp god.h room.h
	${COMPILER} -c god.cpp

room.o: room.cpp room.h roles.h
	${COMPILER} -c room.cpp

roles.o: roles.cpp roles.h headers.h
	${COMPILER} -c roles.cpp

headers.o: headers.cpp headers.h
	${COMPILER} -c headers.cpp

run_input: a.out
	./a.out < input.txt

run: a.out
	./a.out

clean:
	rm *.o
	rm a.out
