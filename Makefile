compile:
	cc -c generator.c
	cc -c pathfinder.c
	cc maze.c generator.o pathfinder.o -o maze -lm
	rm -rf *.o
debug:
	cc -c generator.c
	cc -c pathfinder.c
	cc maze.c generator.o pathfinder.o -o maze -ggdb -lm
	rm -rf *.o