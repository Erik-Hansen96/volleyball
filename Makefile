all: client server

client: client.cc common.h
	g++ -pthread -O3 -g -o client client.cc

server: server.cc common.h
	g++ -pthread -O3 -g -o server server.cc

battleship: battleship.cc
	g++ -pthread -O3 -g -std=c++2a -o battleship battleship.cc

jeopardy: jeopardy.cc
	g++ -pthread -O3 -g -std=c++2a -o jeopardy jeopardy.cc

clean:
	rm -f *.o a.out core
