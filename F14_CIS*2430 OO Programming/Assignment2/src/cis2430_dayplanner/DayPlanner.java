
package cis2430_dayplanner;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Set;

/**
 * Main Class which runs the program.
 * 
 * @author Kyle Hersey, 0851973
 */
public class DayPlanner {
    
    private static MyArrayList <Activity> myList = new MyArrayList<>();
    
    private static HashMap<String,MyArrayList<Integer>> searchMap = new HashMap<>();
    
    /**
     * Main function which operates the control loop for the DayPlanner program,
     * allowing the use to add new activities, and search for existing activities.
     * This function creates the arrays to hold the different activities as well
     * as iterators to keep track of the elements in the array.
     * 
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int key;
        char choice, activityType;
        String inputFileName, outputFileName;
        
        inputFileName = " ";
        outputFileName = " ";
        
        if (args.length == 2) {
            inputFileName = args[0];
            outputFileName = args[1];
        } else if (args.length == 1) {
            outputFileName = args[0];
        }
        
        if (!(inputFileName.equals(" "))) {
            loadListFromFile(inputFileName);
        }
        
        do {
            choice = menu();
            
            if (choice == 'a') {
                
                // START OF ADD BLOCK
                activityType = getActivityType(false);
                if (activityType == 'h') {
                    key = myList.addElement(newHomeActivity());
                    addToHashMap(myList.get(key).getTitle(),key);
                } else if (activityType == 's') {
                    key = myList.addElement(newSchoolActivity());
                    addToHashMap(myList.get(key).getTitle(),key);
                } else if (activityType == 'o') {
                    key = myList.addElement(newOtherActivity());
                    addToHashMap(myList.get(key).getTitle(),key);
                }
                // END OF ADD BLOCK
                
            } else if (choice == 's') {
                
                // START OF SEARCH BLOCK
                
                doSearch();
                
                // END OF SEARCH BLOCK
                
            }
            
        } while (choice != 'q');
        
        if(!(outputFileName.equals(" "))) {
            printListToFile(outputFileName);
        }
        
        System.out.println("Exiting.....\n");
        
    }
    
    
    
    /**
     * Displays a menu with options:
     * Add
     * Search
     * Quit
     * and returns a character representing the user's selected choice.
     * 'a' for Add
     * 's' for Search
     * 'q' for Quit
     * 
     * @return character representing the user's choice
     */
    public static char menu() {
        Scanner input;
        char output = ' ';
        String line;
        
        input = new Scanner(System.in);
        
        System.out.printf("\nPlease Select One of the Following:\n");
        System.out.printf("Add\n");
        System.out.printf("Search\n");
        System.out.printf("Quit\n");
        
        do {
            System.out.printf(">");
            line = input.nextLine();
            
            line = line.toLowerCase().trim();
            
            if(line.equals("a") || line.equals("add")) {
                output = 'a';
            } else if (line.equals("s") || line.equals("search")) {
                output = 's';
            } else if (line.equals("q") || line.equals("quit")) {
                output = 'q';
            } else {
                System.out.printf("Please choose a valid option\n");
            }
            
        } while (output == ' ');
        
        return output;
    }
   
    
    /**
     * Gets the input required to construct a HomeActivity class,
     * creates the class, and returns it to the user
     * 
     * @return a new HomeActivity class
     */
    public static HomeActivity newHomeActivity() {
        HomeActivity newActivity;
        Time startTime, endTime;
        String title, comment;
        Scanner input = new Scanner(System.in);
        
        System.out.printf("\nNEW HOME ACTIVITY\n");
        System.out.printf("Enter Activity Title\n>");
        title = input.nextLine().trim();
        
        System.out.printf("\nEnter Starting Date & Time: \n");
        startTime = newTime();
        
        System.out.printf("\nEnter Ending Date & Time:\n");
        do {
            endTime = newTime();
            if(startTime.compareTo(endTime) >= 0) {
                System.out.printf("Your end time must be later than your start time.\n");
            }
        } while (startTime.compareTo(endTime) >= 0);
        
        System.out.printf("\nEnter Activity Comment\n>");
        comment = input.nextLine();
        
        newActivity = new HomeActivity(title, startTime, endTime, comment);
        return newActivity;
    }
    
    /**
     * Gets the input required to construct a SchoolActivity class,
     * creates the class, and returns it to the user
     * 
     * @return a new SchoolActivity class
     */
    public static SchoolActivity newSchoolActivity() {
        SchoolActivity newActivity;
        Time startTime, endTime;
        String title, comment;
        Scanner input = new Scanner(System.in);
        
        System.out.printf("\nNEW SCHOOL ACTIVITY\n");
        System.out.printf("Enter Activity Title\n>");
        title = input.nextLine().trim();
        
        System.out.printf("\nEnter Starting Date & Time: \n");
        startTime = newTime();
        
        System.out.printf("\nEnter Ending Date & Time:\n");
        do {
            endTime = newTime();
            if(startTime.compareTo(endTime) >= 0) {
                System.out.printf("Your end time must be later than your start time.\n");
            }
        } while (startTime.compareTo(endTime) >= 0);
        
        
        System.out.printf("\nEnter Activity Comment\n>");
        comment = input.nextLine();
        
        newActivity = new SchoolActivity(title, startTime, endTime, comment);
        return newActivity;
    }
    
    /**
     * Gets the input required to construct a OtherActivity class,
     * creates the class, and returns it to the user
     * 
     * @return a new OtherActivity class
     */
    public static OtherActivity newOtherActivity() {
        OtherActivity newActivity;
        Time startTime, endTime;
        String title, comment, location;
        Scanner input = new Scanner(System.in);
        
        System.out.printf("\nNEW OTHER ACTIVITY\n");
        System.out.printf("Enter Activity Title\n>");
        title = input.nextLine().trim();
        
        System.out.printf("\nEnter Activity Location\n>");
        location = input.nextLine().trim();
        
        System.out.printf("\nEnter Starting Date & Time: \n");
        startTime = newTime();
        
        System.out.printf("\nEnter Ending Date & Time:\n");
        do {
            endTime = newTime();
            if(startTime.compareTo(endTime) >= 0) {
                System.out.printf("Your end time must be later than your start time.\n");
            }
        } while (startTime.compareTo(endTime) >= 0);
        
        System.out.printf("\nEnter Activity Comment\n>");
        comment = input.nextLine().trim();
        
        newActivity = new OtherActivity(title, startTime, endTime, comment, location);
        return newActivity;
    }
    
    /**
     * Gets input from the user required to create a new Time class,
     * then constructs the class and returns it to the user.
     * All input is check to ensure it is within a valid range for the
     * respective variable.  For example month must be within 1-12.
     * 
     * @return a new Time class
     */
    public static Time newTime() {
        Time newTime;
        int year=-1, month=-1, day=-1, hour=-1, minute=-1, temp;
        
        Scanner input = new Scanner(System.in);
        
        
        do {
            System.out.printf("Please input date in the following format: yyyy mm dd\n>");
            if (input.hasNextInt()) {
                year = input.nextInt();
                if (input.hasNextInt()) {
                    temp = input.nextInt();
                    if(temp < 13 && temp > 0) {
                        month = temp;
                        if(input.hasNextInt()) {
                            temp = input.nextInt();
                            if(temp < 32 && temp > 0) {
                                day = temp;
                                input.nextLine(); //clear buffer because we are done with it
                            } else {
                                System.out.println("Day does not fall within valid range(1-31)");
                            }
                        } else {
                            input.nextLine(); //clear buffer
                        }
                    } else {
                        System.out.println("Month does not fall within valid range (1-12)");
                    }
                } else {
                    input.nextLine(); //clear buffer
                }
            } else {
                input.nextLine(); //clear buffer
            }
        } while( year == -1 || month == -1 || day == -1);
        
        do {
            System.out.printf("Please input time in the following format: hh mm (hh can be 0-23)\n>");
            if (input.hasNextInt()) {
                temp = input.nextInt();
                if(temp >= 0 && temp < 24) {
                    hour = temp;
                    if(input.hasNextInt()) {
                        temp = input.nextInt();
                        if(temp >= 0 && temp < 60) {
                            minute = temp;
                        } else {
                            System.out.printf("Minute does not fall within valid range (0-59)\n");
                        }
                    } else {
                        input.nextLine();
                    }
                } else {
                    System.out.printf("Hour does not fall within valid range (0-23)\n");
                }
            } else {
                input.nextLine();
            }
        } while( hour == -1 || minute == -1);
        
        newTime = new Time(year, month, day, hour, minute);
        return newTime;
    }
    
    /**
     * Gets the user to select an activity type, and returns it as a character of 
     * the first letter of the activity type.  If empty is true this function will
     * also accept empty input.
     * For example:
     * 'h' for home
     * 's' for school
     * 'o' for other
     * 'newline' for empty
     * 
     * @param empty whether or not the function is allowed to accept empty input
     * @return character representing the user's choice
     */
    public static char getActivityType(boolean empty) {
        String line;
        Scanner input = new Scanner(System.in);
        char output = ' ';
        
        do {
            if (empty) {
                System.out.printf("Please Enter Activity Type (home, school, or other) or press enter for all\n>");
            } else {
                System.out.printf("Please Enter Activity Type (home, school, or other)\n>");
            }
            
            line = input.nextLine().toLowerCase();
            if(line.equals("") && empty) {
                output = '\n';
            } else if(line.trim().equals("home") || line.trim().equals("h")) {
                output = 'h';
            } else if (line.trim().equals("school") || line.trim().equals("s")) {
                output = 's';
            } else if (line.trim().equals("other") || line.trim().equals("o")) {
                output = 'o';
            } else {
                System.out.println("ERROR: invalid activity type entered!");
            }
        } while (output == ' ');
        
        return output;
    }
    
    /**
     * Search through MyArrayList myList for activities. The user can select
     * one or more search types.  Search types:
     * keywords
     * time
     * activity type
     * 
     * Activities which match ALL selected search parameters will be printed 
     * out.
     */
    public static void doSearch() {
        String keywords, temp;
        String [] words;
        char timeSearch, activityType;
        int i;
        boolean toPrint, typeMatch;
        Scanner input;
        Time startTime, endTime;
        MyArrayList <Integer> matchList;
                
        timeSearch = ' ';
        startTime = new Time();
        endTime = new Time();
        input = new Scanner(System.in);
       
        
        
        System.out.printf("Please input your keywords, seperated by spaces, or press enter to skip keyword search\n>");
        keywords = input.nextLine().toLowerCase();
        if(!(keywords.equals("\n"))) {
            keywords = keywords.trim();
        }

        do {
            System.out.printf("Would like to search by time range (y/n)\n>");
            temp = input.nextLine().toLowerCase().trim();
            if(temp.equals("y") || temp.equals("yes")) {
                timeSearch = 'y';
            } else if (temp.equals("n") || temp.equals("no")) {
                timeSearch = 'n';
            }
        } while (timeSearch == ' ');

        if (timeSearch == 'y') {
            System.out.printf("Enter Starting Date & Time: \n");
            startTime = newTime();

            System.out.printf("Enter Ending Date & Time:\n");
            do {
                endTime = newTime();
                if(startTime.compareTo(endTime) >= 0) {
                    System.out.printf("Your end time must be later than your start time.\n");
                }
            } while (startTime.compareTo(endTime) >= 0);
        }

        activityType = getActivityType(true);
        
        if (keywords.equals("\n")) {
            for (i = 0;i < myList.size(); i++) {
                toPrint = false;
                typeMatch = false;

                if (activityType == '\n') {
                    typeMatch = true;
                } else if (activityType == 'h' && myList.get(i) instanceof HomeActivity) {
                    typeMatch = true;
                } else if (activityType == 's' && myList.get(i) instanceof SchoolActivity) {
                    typeMatch = true;
                } else if (activityType == 'o' && myList.get(i) instanceof OtherActivity) {
                    typeMatch = true;
                }

                if(typeMatch == true) {
                    toPrint = true;
                    if (timeSearch == 'y') {
                        toPrint = myList.get(i).inTimeRange(startTime, endTime);
                    }
                }

                if (toPrint) {
                    System.out.printf("%s\n",myList.get(i).toString());
                }
            }
        } else {
            words = keywords.split(" ");
            matchList = new MyArrayList<>();
            typeMatch = false;
            for (String w : words) {
                if(searchMap.containsKey(w)) {
                    if(matchList.isEmpty() && typeMatch == false) {
                        matchList = searchMap.get(w);
                        typeMatch = true;
                    } else {
                        matchList.retainAll(searchMap.get(w));
                    }
                }
            }
            
            if (matchList.isEmpty()) {
                System.out.printf("No activities were found that matched your keywords\n");
            } else {
                for (int key : matchList) {
                    toPrint = false;
                    typeMatch = false;

                    if (activityType == '\n') {
                        typeMatch = true;
                    } else if (activityType == 'h' && myList.get(key) instanceof HomeActivity) {
                        typeMatch = true;
                    } else if (activityType == 's' && myList.get(key) instanceof SchoolActivity) {
                        typeMatch = true;
                    } else if (activityType == 'o' && myList.get(key) instanceof OtherActivity) {
                        typeMatch = true;
                    }

                    if(typeMatch == true) {
                        toPrint = true;
                        if (timeSearch == 'y') {
                            toPrint = myList.get(key).inTimeRange(startTime, endTime);
                        }
                    }

                    if (toPrint) {
                        System.out.printf("%s\n",myList.get(key).printActivity());
                    }
                }
            }
            
        }
        
    }
    
    /**
     * Opens a file "fileName" and reads through it line by line, extracting 
     * Activity data and adding them to MyArrayList myList.
     * 
     * @param fileName the full path of a file from which to load Activities
     */
    public static void loadListFromFile(String fileName) {
        File f;
        BufferedReader br;
        int year, month, day, hour, minute, index;
        String line, title, comment, location, type;
        String[] numArr;
        Time startTime, endTime;
        int key;
        
        f = new File(fileName);
        title = "";
        comment = "";
        location = "";
        startTime = new Time();
        endTime = new Time();
        type = "";
        
        
        try {
            br = new BufferedReader(new FileReader(f));
            while((line = br.readLine()) != null) {
                if(line.startsWith("type=")) {
                    type = line.substring(line.indexOf("=") + 1).trim();
                } else if (line.startsWith("title=")) {
                    title = line.substring(line.indexOf("=") + 1).trim();
                } else if (line.startsWith("startTime=")) {
                    numArr = line.substring(line.indexOf("=")+1).split(" ");
                    year   = Integer.parseInt(numArr[0]);
                    month  = Integer.parseInt(numArr[1]);
                    day    = Integer.parseInt(numArr[2]);
                    hour   = Integer.parseInt(numArr[3]);
                    minute = Integer.parseInt(numArr[4]);
                    startTime = new Time(year, month, day, hour, minute);
                } else if (line.startsWith("endTime=")) {
                    numArr = line.substring(line.indexOf("=")+1).split(" ");
                    year   = Integer.parseInt(numArr[0]);
                    month  = Integer.parseInt(numArr[1]);
                    day    = Integer.parseInt(numArr[2]);
                    hour   = Integer.parseInt(numArr[3]);
                    minute = Integer.parseInt(numArr[4]);
                    endTime   = new Time(year, month, day, hour, minute);
                } else if (line.startsWith("location=")) {
                    location = line.substring(line.indexOf("=") + 1).trim();
                } else if (line.startsWith("comment=")) {
                    comment = line.substring(line.indexOf("=") + 1).trim();
                    if (type.equals("other")) {
                        key = myList.addElement(new OtherActivity(title, startTime, endTime, location, comment));
                        addToHashMap(title,key);
                    } else if (type.equals("home")) {
                        key = myList.addElement(new HomeActivity(title, startTime, endTime, comment));
                        addToHashMap(title,key);
                    } else if (type.equals("school")) {
                        key = myList.addElement(new SchoolActivity(title, startTime, endTime, comment));
                        addToHashMap(title,key);
                    }
                }
            }
            br.close();
        } catch (IOException | NumberFormatException e) {
            System.out.printf("Something went wrong reading file: %s\n",fileName);
            e.printStackTrace(System.out);
        }
        
    }
    
    /**
     * Adds each word in the string "title" to the HashMap searchMap.  If the 
     * particular word already exists in the HashMap, add the key to it's 
     * MyArrayList value. If a particular word does not exist in the HashMap
     * add a new entry.
     * 
     * @param title String containing the title of an Activity.
     * @param key integer which represents the Activity which the title belongs
     * to position within MyArrayList myList.
     */
    public static void addToHashMap(String title, int key) {
        String [] line;
        MyArrayList<Integer> valueList;
        line = title.split(" ");
        
        for(String s : line) {
            if(searchMap.containsKey(s)) {
                searchMap.get(s).addElement(key);
            } else {
                valueList = new MyArrayList<>();
                valueList.addElement(key);
                searchMap.put(s,valueList);
            }
        }
    }
    
    /**
     * Debug function which prints out the hash map in the format:
     * keyword, [ # # # ]
     * where keyword is a string, and the # are all the positions in myList 
     * of Activities which contain the word.
     */
    public static void printHashMap() {
        Set <String> mapKeys;
        MyArrayList<Integer> valueList;
        
        mapKeys = searchMap.keySet();
        for (String s : mapKeys) {
            valueList = searchMap.get(s);
            System.out.printf("%s, [ ",s);
            for (int i : valueList) {
                System.out.printf("%d ", i);
            }
            System.out.printf("]\n");
        }
    }
    
    /**
     * Prints each Activity in MyArrayList myList to a file "fileName".
     * 
     * @param fileName String containing a path to a file.  If it does
     * not already exist it will be created by this method.
     */
    public static void printListToFile(String fileName) {
        PrintWriter writer;
        
        try {
            writer = new PrintWriter(fileName, "UTF-8");
            for(Activity a : myList) {
                writer.printf("%s\n",a.toString());
            }
            writer.close();
        } catch (FileNotFoundException | UnsupportedEncodingException e) {
            System.out.printf("ERROR: something went wrong opening file: %s\n",fileName);
            e.printStackTrace(System.out);
        }
        
    }
}
