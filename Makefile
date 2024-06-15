game_menu.exe: game_menu.c logic.o encrypting_questions.o
	gcc game_menu.c encrypting_questions.o logic.o	-o game_menu.exe
logic.o: logic.c logic.h encrypting_questions.h
	gcc -c logic.c -o logic.o 
encrypting_questions.o : encrypting_questions.c encrypting_questions.h
	gcc -c encrypting_questions.c -o encrypting_questions.o


