CFLAGS  = -Wall -pedantic

demo :
	g++ ${CFLAGS} examples/demo.cpp -o demo 

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

