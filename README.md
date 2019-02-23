<!-- https://github.com/Lexxeous/ping_pong -->

# <img src=".pics/lexx_headshot_clear.png" width="100px"/> Lexxeous's Ping Pong <img src=".pics/ping_pong.jpg" width="130px"/>

The `ping_pong` project is a simple server-client socket program written in C. A server runs in the background on port 10001+ and awaits for the client to send a message. If the client sends `ping`, the server responds with `pong`, otherwise, the server will return the same string that was sent. The program runs on `localhost` using TCP.

### Prerequisites
 * [make](http://www.gnu.org/software/make/)
 * [gcc](https://gcc.gnu.org/install/)
 * [g++](http://www1.cmc.edu/pages/faculty/alee/g++/g++.html) `OPTIONAL`

### MacOSX Instructions

1. Navigate to project folder.
2. Open 2 terminal windows in the project directory.
3. Execute `make run_s` to spin up the server in one of the terminal windows.
4. Take note of the port number that the server is running on (10001 ~ 10101).
5. Open the other terminal window and execute `make run_c port=<port_num>` to start the client on port `<port_num>`.
6. Send strings to the server from the client and observe the response. Send `ping` and get `pong`.
7. Stop both the server and the client by typing `CTRL+c` in their respective windows.
8. Execute `make clean` to remove the server and client executables from the directory.

### Windows Instructions

... in progress ...
