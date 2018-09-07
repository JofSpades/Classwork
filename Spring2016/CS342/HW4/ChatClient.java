/*
 *  Maxwell Petersen; Tony Wong
 *  CS 342 - Project 4
 *  
 *  The client side of our chat program that also doubles as the GUI.
 *      
 *  -------------------------------------------------
 *  | Usernames | Messages from server show up here |
 *  | show up   |                                   |
 *  | here      |                                   |
 *  |           |                                   |
 *  |           |                                   |
 *  |           |                                   |
 *  |           |                                   |
 *  |           |                                   |
 *  |           |                                   |
 *  |           |                                   |
 *  |           |                                   |
 *  -------------------------------------------------
 *  | User types their message here                 |
 *  -------------------------------------------------
 *
 *
 *  What happens when the ChatClient is executed:
 *      1) Prompts user for IP address of Server
 *         Port number is set to 13337
 *      2) Connects to server and waits for response
 *      3) Once client thread is created, prompt user for username
 *         Will continually re-prompt if username is already taken
 *      4) Once username is accepted, the GUI text area will unlock
 *         and user will be able to type. Client is now waiting for
 *         server messages or user input from text field.
 *         Client can receive two types of messages:
 *              a) %%MESSAGE - a regular or private message
 *                 gets displayed within the server messages area
 *              b) %%UPDATE - informs the client to update username
 *                 list because of new user or other user leaving
 */

import java.awt.event.*;
import java.io.*;
import java.net.*;
import javax.swing.*;

public class ChatClient {
    // thread client variables
	BufferedReader in;      // incoming byte-stream from server to client
	PrintWriter out;        // outgoing byte-stream to server from client
	JFrame frame = new JFrame("CS 342 - Chat Client");      // GUI frame
	JTextField textField = new JTextField(40);      // where the user types
	JTextArea userField = new JTextArea(10, 10);    // shows who is currently connected
	JTextArea messageArea = new JTextArea(10, 40);  // shows all received messages
	String username;                                // the username of client thread
    int port = 13337;                               // the default server port

	// constructor for actual client
	public ChatClient() {
		// disable all elements until needed
		textField.setEditable(false);
		userField.setEditable(false);
		messageArea.setEditable(false);

		// format GUI as detailed in comment header
		frame.getContentPane().add(textField, "South");
		frame.getContentPane().add(userField, "West");
		frame.getContentPane().add(new JScrollPane(messageArea), "Center");
		frame.pack();

		// listens for client message, sends when user hits enter after typing message
		textField.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// send out typed message to server
				out.println(textField.getText());

				// clear input box for next message
				textField.setText("");
			}
		});
	}

	// prompts the user to enter the server ip address
	private String getServerAddress() {
		return JOptionPane.showInputDialog(
			frame,
			"IP Address:",
			"Troy A'hoy!",
			JOptionPane.QUESTION_MESSAGE);
	}

	// prompts the user to enter in a username that is seen by everyone
	private String getName() {
		return JOptionPane.showInputDialog(
			frame,
			"Username:",
			"Enter username",
			JOptionPane.PLAIN_MESSAGE);
	}

	// thread job for client
	private void run() throws IOException {
		// prompts user for server's IP address and store value
		String serverAddress = getServerAddress();

		// open socket to server
		Socket socket = new Socket(serverAddress, port);

		// open incoming byte stream
		in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

		// open outgoing byte stream
		out = new PrintWriter(socket.getOutputStream(), true);

		// infinite loop that checks for messages from server
		while (true) {
			// get input from server
			String line = in.readLine();

			// server is requesting a username
			if (line.startsWith("%%INPUTNAME")) {
				// get the name from user
				String name = getName();

				// used if user wants to be anonymous
				InetAddress ip = InetAddress.getLocalHost();

				// send the server the requested name
				out.println((name.length() == 0 || name == null) ?      // ternary operator
                            ("user@"+ip.getHostAddress()) :     // anonymous case
                            name);                              // entered username case
            }

			// server has accepted username
			else if (line.startsWith("%%NAMEACCEPTED")) {
				// enables user to start chatting
				textField.setEditable(true);

				// rename the titlebar of the client's GUI to username
				line = line.replaceFirst("%%NAMEACCEPTED ", "");
				this.frame.setTitle(line);
            }

			// server has sent client a message
			else if (line.startsWith("%%MESSAGE")) {
				// remove header
				line = line.replaceFirst("%%MESSAGE ", "");

				// display the message
				messageArea.append(line + "\n");
            }

			// server is telling client to update the list of active users
			else if (line.startsWith("%%UPDATE")) {
				// remove header
				line = line.replaceFirst("%%UPDATE ", "");

				// change delimiters to newlines for formatting
				line = line.replaceAll("@@@", "\n");

				// clear active user list before displaying update
				userField.setText(null);

				// display active users connected to server
				userField.append(line);
			}
		}
	}

	// main function that starts up the client
	public static void main(String[] args) throws Exception {
        // create client thread
		ChatClient client = new ChatClient();

		// client disconnects from server by closing the frame window
		client.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// show the GUI
		client.frame.setVisible(true);

		// start the client thread
		client.run();
	}
}
//EOF
