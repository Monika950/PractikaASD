main.exe: main.c logic.o
	gcc main.c logic.o	-o main.exe
logic.o: logic.c logic.h
	gcc -c logic.c -o logic.o