Partners: Maxwell Petersen, Tony Wong

-EXTRA CREDIT IS IMPLEMENTED! See ** below.

-The default server port is 13337.
-Input an IP address of 127.0.0.1 if testing on a single machine.

-The server and client talk to each other through messages prefixed
 with certain headers that are invisible to the user.
	%%INPUTNAME 		Used to request a username to be sent to the server
	%%NAMEACCEPTED 		Used to signify thatt the name sent to the server is valid
	%%MESSAGE 			Used to state the string is a message to be displayed
	%%UPDATE			Used to state the string is an update

-A user can broadcast a message by simply typing and hitting enter.
 This will send a message to all active connected clients.
 This means there are no buttons to specify how to send the message.
 Everything is done through the text box.

**A user can specify one or more individuals to send a message by
  including a comma-separated list of usernames followed by %% and
  their message.

    EXAMPLES:
        If Alice wants to send the message "Hello!" to Bob and Susan, then
        Alice will input the following in her chat client:

            Bob,Susan%%Hello!


        If Alice only wants to send to Bob:

            Bob%%Hello!

