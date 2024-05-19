# FIFO chat exercise
Just a short C code allowing for sending messages between two processes using fifo file.

Communication is highly synchronous: one must send a message to the other, for them to be able to send a message back (server is the one sending the message first).

Communication ends when message "Bye" is sent.

*I know including a C file isn't a very good practise*

### Usage
In terminal write:
```
$ make
```

Then in one terminal write:
```
$ ./server.out
```

And in another:
```
$ ./client.out
```

Make sure you run server before the client, because server creates fifo file needed for the client to run.