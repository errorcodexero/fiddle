package com.deathcode;

import java.io.*;
import java.util.ArrayList;

import java.util.Scanner;

/*import java.util.Map;
import java.util.HashMap;
import java.util.List;
*/

public class LogReader {
	///private static Map <String, Integer> columnMap = new HashMap<String, Integer>();
	//private static ArrayList<String> columnNames = new ArrayList<String>();
	private static File file;
	private static CSVReader csv;

	public static void main(String[] args) throws IOException {  
    	Scanner reader = new Scanner(System.in);
    	System.out.println("Enter a file: ");
    	String fileName = reader.next();
    	String line;

    	file = new File(fileName);
    	if(file.exists() && !file.isDirectory()) {
        	csv = new CSVReader(file);
    	} else {
    		while(!file.exists() || file.isDirectory()) {
    			if (!file.exists()) {
    				System.out.println("File Does Not Exist.\nEnter A File: ");
    				fileName = reader.next();
    			} else if (file.isDirectory()) {
    				System.out.println("File is a Directory.\nEnter A File: ");
    				fileName = reader.next();
    			}
    			if (file.exists() && !file.isDirectory())
    				break;
    		
    		}
    	}
    	reader.close();
    	ArrayList<String> data = new ArrayList<String>();
    	data = csv.getDividedLine(file, 4);
    	for (int i = 1; i < data.size(); i++) {
    		//System.out.println(data.elementAt(i));
    	}
    	//columnNames = csv.getDividedLine(file, 1);
    	int i = 1;
    	while ((line = CSVReader.readLine(file, i)) != "ERROR") {
    		System.out.println(line);
    		i++;
    	};
    }
	
}


