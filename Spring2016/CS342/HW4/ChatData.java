/*
 *  Maxwell Petersen; Tony Wong
 *  CS 342 - Project 4
 *
 *  An object that contains the printwriter-username pair representing a client.
 *  Used so the server can identify who's who.
 */

import java.io.*;
import java.util.*;
import java.net.*;

public class ChatData{
    private PrintWriter writer;       // holds the outstream to client (instream for client)
    private String name;              // holds the client's username

    public ChatData(PrintWriter writer, String name){
        this.writer = writer;
        this.name = name;
    }

    // gets the correct outstream so that the server can send messages to the correct client
    public PrintWriter getWriter(){
        return this.writer;
    }

    // gets the username of the client
    public String getName(){
        return this.name;
    }
}
//EOF
