run_s: server
	./server # run server executable

run_c: client
	./client $(port) # run client executable with port parameter

server:
	gcc -o server server.c pingpong.c # compile and link into a "server" executable

client:
	gcc -o client client.c pingpong.c # compile and link into a "client" executable

clean:
	rm server client # delete executables

