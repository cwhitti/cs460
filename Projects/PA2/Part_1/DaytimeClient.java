import java.io.IOException;
import java.net.Socket;
import java.io.DataInputStream;

public class DaytimeClient
    {
     static Socket socket;
     // static String SERVER_HOST = "108.174.197.222";
     static String SERVER_HOST = "time.nist.gov";
     static int PORT = 13;
     static char OTM = '*';

    public static void main(String[] args) throws IOException
        {
         Socket socket = new Socket(SERVER_HOST, PORT);
         DataInputStream fromServer = new DataInputStream(socket.getInputStream());
         byte[] serverData = new byte[50];
         int index;

         System.out.println("Daytime Client");

         if (socket.isConnected())
            {
             System.out.println("Connected successfully to " + SERVER_HOST + " on port " + PORT);
            }
         else
            {
             System.out.println("Failed to connect to " + SERVER_HOST + " on port " + PORT);
            }

         // read first character of input
         fromServer.readFully(serverData);
         index = 0;

         while (serverData[index] != OTM)
            {
             // print read character
             System.out.print((char)serverData[index]);

             // read the next character
             index++;
            }

         // print new line
         System.out.println();

         socket.close();
        }
    }
