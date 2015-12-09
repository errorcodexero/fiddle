import java.io.*;
import java.net.*;

public class Client{
	public static void main(String[] args) throws Exception{
		Client c = new Client();
		c.run();
	}
	public void run() throws Exception{
		Socket sock = new Socket("0.0.0.0",6666);
		
		InputStreamReader IR = new InputStreamReader(sock.getInputStream());
		BufferedReader BR = new BufferedReader(IR);
		
		while(true){
			String msg = BR.readLine();
			System.out.println(msg);
		}
	}
}
