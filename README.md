TCP Echo Client/Server
======================

The two sets of programs included are a TCP Client and Server using sockets
through the Linux system call API. The server uses port 8080. The client 
will periodically(every second) send a message and a count to the server.
The server will then echo back the response and the client will print the 
string being sent. The server is capable of handling multiple connections 
and will spawn processes for each connection.

Building instructions
---------------------

    $ make

Usage
-----
    $ server
    $ client ip port

#### Examples

    server
    client 127.0.0.1 8080

Contact
-------

The author can be reached at 
vaibhav.kapoor06@gmail.com
