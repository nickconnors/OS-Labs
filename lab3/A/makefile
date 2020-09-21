all: Proc1 Proc2 Proc3 Proc4

ssem.o: ssem.c
	gcc -c ssem.c -o ssem.o

sshm.o: sshm.c
	gcc -c sshm.c -o sshm.o

Proc1: Proc1.c ssem.o sshm.o
	gcc Proc1.c ssem.o sshm.o -o Proc1

Proc2: Proc2.c ssem.o sshm.o
	gcc Proc2.c ssem.o sshm.o -o Proc2

Proc3: Proc3.c ssem.o sshm.o
	gcc Proc3.c ssem.o sshm.o -o Proc3

Proc4: Proc4.c ssem.o sshm.o
	gcc Proc4.c ssem.o sshm.o -o Proc4

clean:
	find . -type f -executable -exec rm '{}' \;
