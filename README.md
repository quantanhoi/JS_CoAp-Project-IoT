# CoAp Client-Server Javascript
Code Example for Client-Server Communication using node-CoAp in Javascript
Documentation: https://github.com/coapjs/node-coap
Also a C++ code example for reading server output using pipe
## Usage

To use the client, write this into a terminal:
```
node coap_client.js
```
Similarly, to use the client 2, write this into another terminal
```
node coap_client2.js
```
To run the server with node
```
node coap_server.js
```
To compile the C++ read server output:
```
g++ read_server_output.cpp -o read_server_output
```
Run the compiled C++ Program:
```
./read_server_output
```
Then you can input E then enter to send the message to the server on localhost

```
sudo apt-get update
sudo apt-get install build-essential tk-dev libncurses5-dev libncursesw5-dev libreadline6-dev libdb5.3-dev libgdbm-dev libsqlite3-dev libssl-dev libbz2-dev libexpat1-dev liblzma-dev zlib1g-dev libffi-dev
wget https://www.python.org/ftp/python/3.10.2/Python-3.10.2.tgz
tar -xvf Python-3.10.2.tgz
cd Python-3.10.2


```
