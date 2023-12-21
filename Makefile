compile:
	cc -c generator.c
	cc maze.c generator.o -o maze -lm
	rm -rf *.o
debug:
	cc -c generator.c
	cc maze.c generator.o -o maze -ggdb -lm
	rm -rf *.o