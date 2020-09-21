all: lab2

lab2: AA.c BB CC DD EE FF
	gcc -ansi -g AA.c -o lab2

BB: BB.c
	gcc -ansi -g BB.c -o BB

CC: CC.c
	gcc -ansi -g CC.c -o CC

DD: DD.c
	gcc -ansi -g DD.c -o DD

EE: EE.c
	gcc -ansi -g EE.c -o EE

FF: FF.c
	gcc -ansi -g FF.c -o FF

clean:
	find . -type f -executable -exec rm '{}' \;
