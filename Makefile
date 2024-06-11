game_menu.exe: game_menu.c logic.o
	gcc game_menu.c logic.o	-o game_menu.exe
logic.o: logic.c logic.h
	gcc -c logic.c -o logic.o
