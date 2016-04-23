package com.deathcode;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CSVReader {

	public static File file;
	
    public CSVReader(File inputFile) {
    	file = inputFile;
    }
    public static String readLine(File file, int lineNumber) throws IOException {
    	String line = "";
    	int itr = 0;
    	RandomAccessFile fileStream = new RandomAccessFile(file, "rw");
    	try {
    		fileStream.seek(0);
    		while (itr != lineNumber) {
    			line = fileStream.readLine();
    			itr++;
    		}
    	} finally {
    		if (fileStream != null)
    			fileStream.close();
    	}
    	fileStream.close();
    	System.out.println(line);
    	return line;
    }
    
    public float parseStringForFloats(String raw) throws NumberFormatException {
    	float output = 0;
    	Pattern p = Pattern.compile("[-]?[0-9]*\\.?[0-9]+");
    	
    	Matcher m = p.matcher(raw);
    	m.find();
    	output = java.lang.Float.parseFloat(m.group());

    	return output;
    }
    
    public ArrayList<String> breakByDelimiter (String string, char delimiter) {
    	char tempChar = '\0';
    	String tempString = "";
    	ArrayList<String> output = new ArrayList<String>();
    	
    	for (int i = 0; i < string.length(); i++) {
    		tempChar = string.charAt(i);
    		if (tempChar == delimiter) {
    			output.add(tempString);
    			tempString = "";
    		} else if (tempChar == '\n') {
    			output.add(tempString);
    			tempString = "";
    		}
    		else
    			tempString += tempChar;
    	}
    	
    	return output;
    }  
    
    public ArrayList<String> getDividedLine(File file, int lineNumber) throws IOException {
    	String line = "";
    	ArrayList<String> output = new ArrayList<String>();
    	
    	line = readLine(file, lineNumber);
    	output = breakByDelimiter (line, ',');
    	
    	return output;
    }
    public ArrayList<String> getCSVHeader(File file) throws IOException {
    	ArrayList<String> output = new ArrayList<String>();
    	String line = "";
    	line = readLine(file, 1);
    	output = breakByDelimiter (line, ',');
    	return output;
    	
    }
    public String getElement(File file, int lineNumber, int elementNumber) throws IOException{
    	String line = "";
    	String output = "";
    	ArrayList<String> brokenLine;
    	line = readLine(file, lineNumber);
    	brokenLine = breakByDelimiter(line, ',');
    	
    	for (int i = 0; i <= brokenLine.size(); i++) {
    		if (i == elementNumber) {
    			output = brokenLine.get(i);
    			break;
    		} else
    			output = "";
    	}
    	
    	return output;
    }
	
}
