PROJECT = library.a
OBJECTS = logger.o rotator.o file_handler.o memory_handler.o
CFLAGS  = -Wall -pedantic

demo: ${OBJECTS} demo.o
	g++ demo.o ${OBJECTS} -o demo

demo.o : examples/demo.cpp
	g++ -c $(CFLAGS) -Isrc examples/demo.cpp
logger.o : src/logger.cpp
	g++  -c $(CFLAGS) -Isrc src/logger.cpp
memory_handler.o : src/handlers/memory_handler.cpp
	g++ -c $(CFLAGS) -Isrc src/handlers/memory_handler.cpp
file_handler.o : src/handlers/file_handler.cpp
	g++ -c $(CFLAGS) -Isrc src/handlers/file_handler.cpp
rotator.o : src/handlers/file_manipulators/rotator.cpp
	g++ -c $(CFLAGS) -Isrc src/handlers/file_manipulators/rotator.cpp

clean-all:
	rm -rf *.o
	rm demo
	rm -rf logs*
	rm -rf log
clean:
	rm -rf *.o
	rm demo
clean-logs:
	rm -rf logs*
	rm -rf log

