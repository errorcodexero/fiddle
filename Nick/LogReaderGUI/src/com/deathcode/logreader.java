package com.deathcode;

import java.io.*;
import java.util.Vector;

import com.sun.org.apache.bcel.internal.classfile.Attribute;

import java.util.Map;
import java.util.Scanner;
import java.util.HashMap;
import java.util.List;

import javafx.application.Application;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableColumn.CellDataFeatures;
import javafx.scene.control.TableView;
import javafx.scene.control.TitledPane;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.control.ScrollPane;
import javafx.stage.Stage;
import javafx.util.Callback;


public class logreader extends Application  {
	public static Map <String, Integer> columnMap = new HashMap<String, Integer>();
	public static Vector<String> columnNames = new Vector<String>();
	public static File file;
	public static CSVReader csv;
	private static Vector<TableColumn> columns;
	
	private ScrollPane scrollpane;
	private GridPane gridpane;
	private TitledPane titlepane;
	private Button getAvg;
	private Button getMax;
	private Button getMin;
	private TableView table;
	private Button getDataElement;
	private Button whenDid;
	private Button getTimeStats;
	private Button getLogStats;
 
	public static void main(String[] args) throws IOException {  
    	Scanner reader = new Scanner(System.in);
    	System.out.println("Enter a file: ");
    	String fileName = reader.next();

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
    	Vector<String> data = new Vector<String>();
    	data = csv.getDividedLine(file, 4);
    	for (int i = 1; i < data.size(); i++) {
    		//System.out.println(data.elementAt(i));
    	}
    	columnNames = csv.getDividedLine(file, 1);
    	columns = new Vector<TableColumn>(columnNames.size(),0);
		//table.setEditable(true);
    	launch(args);
    }
	
	public void start(Stage stage) throws Exception {
		TitledPane titlepane = (TitledPane) FXMLLoader.load(getClass().getResource("main.fxml"));
		Scene scene = new Scene(titlepane, 701, 410);
		
		for (int i = 1; i < columnNames.size(); i++) {
			columns.add(new TableColumn(/*columnNames.elementAt(i)*/ "3"));
		}
		for (int i = 1; i < columns.size(); i++) {
			columns.elementAt(i).setCellValueFactory(new PropertyValueFactory<>("CSVData"));
		}
		titlepane.setContent(gridpane);
		
		stage.setTitle("Test");
		stage.setScene(scene);
		stage.show();
	}
	public static class CSVData {
		private final SimpleStringProperty Data;
		
		private CSVData(String inputData) {
			this.Data = new SimpleStringProperty(inputData);
		}
		public String getData() {
			return Data.get();
		}
		public void setData(String inputData) {
			Data.set(inputData);
		}
	}
	public void initialize() {
		assert scrollpane != null : "ERROR";
		assert table != null : "ERROR";
	}

}


