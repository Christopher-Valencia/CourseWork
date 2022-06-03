Christopher Valencia
Project 01
--------------------------------------------------------------------------------------------
There are two directories, one is server and one is client, they both have a "files" folder
within. This is where the sent and received files are sent from and stored to.

You must have two terminals open in order to run the client on one and server on the other.

The message format is the same as the TFTP protocal dictates:
            2 bytes     string    1 byte     string   1 byte
            ------------------------------------------------
           | Opcode |  Filename  |   0  |    Mode    |   0  |
            ------------------------------------------------
			Read/Write Request
and
		   2 bytes     2 bytes      n bytes
                   ----------------------------------
                  | Opcode |   Block #  |   Data     |
                   ----------------------------------

                        	DATA packet
for example if client sends:
"01test.txt0netascii0"

This command will initiate a read request from the file test.txt and store it in the client's
file folder within its directory.

for example if client sends:
"02clientTestFile.txt0netascii0"

This command will initiate a write to the server from the client files folder and store it in
the server's files folder