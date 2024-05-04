all: prog.exe

prog.exe: main.o func.o
	gcc -o prog main.o func.o

main.o: main.c func.h
	gcc -c --std=c99 -o  main.o  main.c

func.o: func.c func.h
	gcc -c --std=c99 -o func.o func.c

clean:
	del *.o
	del prog.exe