all:
	g++ server.cpp -o server
run:
	./server &
kill:
	killall server
e:
	nano -c server.cpp
