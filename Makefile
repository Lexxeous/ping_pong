run_s: server
	./server

run_c: client
	./client $(port)

server:
	gcc -o server server.c pingpong.c

client:
	gcc -o client client.c pingpong.c

clean:
	rm server client

