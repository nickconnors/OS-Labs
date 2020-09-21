all: PipeC

PipeC: PipeC.c PipeW1 PipeW2 PipeR
	gcc PipeC.c -o PipeC

PipeW1: PipeW1.c
	gcc PipeW1.c -o PipeW1

PipeW2: PipeW2.c
	gcc PipeW2.c -o PipeW2

PipeR: PipeR.c
	gcc PipeR.c -o PipeR

clean:
	find . -type f -executable -exec rm '{}' \;
