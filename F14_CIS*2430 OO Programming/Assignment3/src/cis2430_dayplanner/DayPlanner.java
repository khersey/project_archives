
package cis2430_dayplanner;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.HashMap;
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
     * Launches the GUI.
     * 
     * @param args the command line arguments
     */
    
    public static void main(String[] args) {
        int key;
        char choice, activityType;
        String inputFileName, outputFileName;
        
        inputFileName = "";
        outputFileName = "";
        
        if (args.length == 2) {
            inputFileName = args[0];
            outputFileName = args[1];
        } else if (args.length == 1) {
            outputFileName = args[0];
        }
        
        if (!(inputFileName.trim().equals(""))) {
            loadListFromFile(inputFileName);
        }
        
        javax.swing.SwingUtilities.invokeLater(() -> {
            GUI gui = new GUI();
            gui.setVisible(true);
        });
        
        
        if(!(outputFileName.trim().equals(""))) {
            printListToFile(outputFileName);
        }
        
        System.out.println("Exiting.....\n");
        
    }
    
    /**
     * Adds a HomeActivity to the MyArrayList myList.
     * 
     * @param ha HomeACtivity to be added.
     */
    public static void addHomeActivity(HomeActivity ha) {
        int key;
        key = myList.addElement(ha);
        addToHashMap(myList.get(key).getTitle(),key);
    }
    
    /**
     * Adds a SchoolActivity to the MyArrayList myList.
     * 
     * @param sa SchoolActivity to be added.
     */
    public static void addSchoolActivity(SchoolActivity sa) {
        int key;
        key = myList.addElement(sa);
        addToHashMap(myList.get(key).getTitle(),key);
    }
    
    /**
     * Adds an OtherActivity to the MyArrayList myList.
     * 
     * @param oa OtherActivity to be added.
     */
    public static void addOtherActivity(OtherActivity oa) {
        int key;
        key = myList.addElement(oa);
        addToHashMap(myList.get(key).getTitle(),key);
    }
    
    /**
     * Search through MyArrayList myList for activities. The user can select
     * one or more search types.  Search types:
     * keywords
     * time
     * activity type
     * 
     * Activities which match ALL selected search parameters will be returned
     */
    public static MyArrayList<String> doSearch(String type, String keywords, Time startTime, Time endTime) {
        String temp;
        String [] words;
        MyArrayList <String> output = new MyArrayList();
        int i;
        boolean toPrint, typeMatch;
        MyArrayList <Integer> matchList;
              
        if (keywords.trim().equals("")) {
            for (i = 0;i < myList.size(); i++) {
                toPrint = false;
                typeMatch = false;

                if (type.equals("All")) {
                    typeMatch = true;
                } else if (type.equals("Home") && myList.get(i) instanceof HomeActivity) {
                    typeMatch = true;
                } else if (type.equals("School") && myList.get(i) instanceof SchoolActivity) {
                    typeMatch = true;
                } else if (type.equals("Other") && myList.get(i) instanceof OtherActivity) {
                    typeMatch = true;
                }

                if(typeMatch == true) {
                    toPrint = true;
                    if (startTime != null && endTime != null) {
                        toPrint = myList.get(i).inTimeRange(startTime, endTime);
                    }
                }

                if (toPrint) {
                    output.addElement(myList.get(i).printActivity());
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
            
            if (!(matchList.isEmpty()))  {
                for (int key : matchList) {
                    toPrint = false;
                    typeMatch = false;

                    if (type.equals("All")) {
                        typeMatch = true;
                    } else if (type.equals("Home") && myList.get(key) instanceof HomeActivity) {
                        typeMatch = true;
                    } else if (type.equals("School") && myList.get(key) instanceof SchoolActivity) {
                        typeMatch = true;
                    } else if (type.equals("Other") && myList.get(key) instanceof OtherActivity) {
                        typeMatch = true;
                    }

                    if(typeMatch == true) {
                        toPrint = true;
                        if (startTime != null && endTime != null) {
                            toPrint = myList.get(key).inTimeRange(startTime, endTime);
                        }
                    }

                    if (toPrint) {
                        output.addElement(myList.get(key).printActivity());
                    }
                }
            }
            
        }
        if (output.size() == 0) {
            output.addElement("No entries were found that matched your criteria\n");
        }
        
        return output;
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
