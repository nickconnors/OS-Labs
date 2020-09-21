all: ProcW ProcX ProcY ProcZ

ssem.o: ssem.c
	gcc -c ssem.c -o ssem.o

sshm.o: sshm.c
	gcc -c sshm.c -o sshm.o

ProcW: ProcW.c ssem.o sshm.o
	gcc ProcW.c ssem.o sshm.o -o ProcW

ProcX: ProcX.c ssem.o sshm.o
	gcc ProcX.c ssem.o sshm.o -o ProcX

ProcY: ProcY.c ssem.o sshm.o
	gcc ProcY.c ssem.o sshm.o -o ProcY

ProcZ: ProcZ.c ssem.o sshm.o
	gcc ProcZ.c ssem.o sshm.o -o ProcZ

clean:
	find . -type f -executable -exec rm '{}' \;
