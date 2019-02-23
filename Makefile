# set default varibles
port?=10001
tcp_port?=10001

run_s: server
	./server # run server executable

run_c: client
	./client $(port) # run client executable with port parameter

server:
	gcc -o server server.c ping_pong.c # compile and link into a "server" executable

client:
	gcc -o client client.c ping_pong.c # compile and link into a "client" executable

clean:
	rm server client # delete executables

pid:
	lsof -i tcp:$(tcp_port)

pids:
	lsof -i tcp:10001
	lsof -i tcp:10002
	lsof -i tcp:10003

kill_s:
	kill `pgrep server`

kill_c:
	kill `pgrep client`

