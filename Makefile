all: volleypardyship

volleypardyship: jeopardy.cc  battleship.cc common.h
	g++ -pthread -g -std=c++2a jeopardy.cc battleship.cc -o volleypardyship

clean:
	rm -f *.o a.out core
