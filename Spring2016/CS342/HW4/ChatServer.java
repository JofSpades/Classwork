/*
 *  Maxwell Petersen; Tony Wong
 *  CS 342 - Project 4
 *   
 *  The server side of our chat program. The default port is 13337.
 *
 *  What happens when the ChatServer is executed:
 *      1) Server listens on port 13337
 *      2) If server accepts a connection, then it spins off a thread
 *         to handle the client.
 *         The client thread enters the following process:
 *              a) Keep asking the client for a username until it's valid.
 *                 Informs everyone that a new user has connected.
 *              b) Now waiting for input from client
 *                  -Messages can either be private or public broadcast
 *                  -Private messages contain the %% delimiter (more in README)
 *              c) Client ends when user closes window.
 *                 Server informs everyone that this client has disconnected.
 */

import java.io.*;
import java.net.*;
import java.util.*;

public class ChatServer {
    // the default server port
	private static final int PORT = 13337;

    // hash table to store a unique set of usernames
	private static HashSet<String> names = new HashSet<String>();

    // hash table that stores a unique set of usernames paired with their printwriter
    // allows for communication to a specific user(s)
	private static HashSet<ChatData> storedData = new HashSet<ChatData>();

	// main program and thread creator
	public static void main(String[] args) throws Exception {
        System.out.println("Server is up and running.");
        // opens up the serversocket for the world to see
        ServerSocket listener = new ServerSocket(PORT);
        try {
            // while the program is running
            while (true) {
                // spin up a new thread and start it from an accepted connection
                new Handler(listener.accept()).start();
            }
        }
        finally {
            //kill the connection
            listener.close();
        }
    }

	// function to update the list of active connected users
	public static void updateUsers() {
        // header for client to know that its an update
		String updateMsg = "%%UPDATE ";

        // gets all the names in a special delimited list to send
		for(ChatData data: storedData){
			updateMsg += data.getName();
			updateMsg += "@@@";
		}

        // tell everyone to update their user list
		for(ChatData data: storedData){
			data.getWriter().println(updateMsg);
		}
	}

    // how the server spins off a new thread for a new client
	private static class Handler extends Thread {
		private String name;            // stores client's username
		private Socket socket;          // client socket
		private BufferedReader in;      // incoming byte-stream from client to server
		private PrintWriter out;        // outgoing byte-stream from server to client
        private ChatData identity;      // printwriter-username pair

        // thread instance constructor which saves the passed in socket
		public Handler(Socket socket) {
			this.socket = socket;
		}

        // server execution loop
		public void run() {
			try {
                // setup incoming/outgoing byte-streams
				in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
				out = new PrintWriter(socket.getOutputStream(), true);

                // repeatedly ask the user for a username until it's valid
			    while (true) {
                    // ask client for a username
				    out.println("%%INPUTNAME");
				    name = in.readLine();

                    // if the user closes the prompt
				    if (name == null) {
					    return;
				    }

                    // check the relevent data-structures for uniqueness
				    synchronized (names) {
					    synchronized(storedData){
                            // check if username isn't already used
						    if (!names.contains(name)) {
                                // add it to the list if unique
							    names.add(name);

                                // store the printwriter-username pair
                                identity = new ChatData(out, name);
							    storedData.add(identity);

                            // break out of asking for a username
						    break;
					        }
				        }
			        }
		        }

                // let the client know that the name was accecpted
				out.println("%%NAMEACCEPTED " + name);

                // let everyone know that the client is active and what their name is
				for(ChatData data: storedData){
					data.getWriter().println("%%MESSAGE "+name+" has connected.");
				}

                // tell everyone to update their username list
				updateUsers();

                // the infinite loop that handles client messages
				while (true) {
                    // get input from client
					String input = in.readLine();

                    // if nothing, then something failed
					if (input == null) {
						return;
					}

                    // attempt to parse for private chat
					String[] splitUp = input.split("%%");
          
                    // if only one element in splitUp then it's a group message
					if(splitUp.length == 1){
                        //send to everyone
						for(ChatData data:storedData){
							data.getWriter().println("%%MESSAGE <"+name+"> "+input);
						}
					}
                    else {
                    // else find the individuals that need the message and send to them
						for(ChatData data:storedData){
							if(splitUp[0].contains(data.getName()) || data.getName().equals(name)){
								data.getWriter().println("%%MESSAGE <PRIVATE:"+name+"> "+splitUp[1]);
							}
						}
					}
				}
            }

            // catch any IO errors
            catch (IOException e) {
				System.out.println(e);
			} 

            // what to do once user closes window
            finally {
				if(name != null || out != null){
					storedData.remove(identity);
				}
				try {
					socket.close();
				}
                catch (IOException e) {}

                // tell everyone to update their user list because client disconnected
				updateUsers();
				for(ChatData data:storedData){
					data.getWriter().println("%%MESSAGE "+name+" has disconnected.");
				}
			}
		}
	}
}
//EOF
