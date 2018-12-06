#_*_Makefile_*_

#target: dependencies
#	action

#final is executable file
final: creating_entry.o main.o
	gcc -o final main.o creating_entry.o

test.o: test.c rt.h
	gcc -c test.c

creating_entry.o: creating_entry.c rt.h
	gcc -c creating_entry.c

clean:
	rm *.o
