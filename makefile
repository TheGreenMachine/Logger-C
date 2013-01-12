PROJECT = library.a
CFLAGS  = -Wall -pedantic

demo :
	g++ demo.cpp  2> error

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

