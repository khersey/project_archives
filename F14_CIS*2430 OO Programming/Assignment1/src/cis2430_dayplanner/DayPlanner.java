/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430_dayplanner;

import java.util.Scanner;

/**
 * Main Class which runs the program.
 * 
 * @author Kyle Hersey, 0851973
 */
public class DayPlanner {

    /**
     * Main function which operates the control loop for the DayPlanner program,
     * allowing the use to add new activities, and search for existing activies.
     * This function creates the arrays to hold the different activities as well
     * as iterators to keep track of the elements in the array.
     * 
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        HomeActivity homeArray[] = new HomeActivity[64];
        int homeArrayCount = 0;
        SchoolActivity schoolArray[] = new SchoolActivity[64];
        int schoolArrayCount = 0;
        OtherActivity otherArray[] = new OtherActivity[64];
        int otherArrayCount = 0;
        
        char choice, activityType, timeSearch = ' ';
        String keywords, temp;
        Time startTime = new Time(), endTime = new Time();
        Scanner input = new Scanner(System.in);
        int i;
        boolean toPrint;
        
        do {
            choice = menu();
            
            if (choice == 'a') {
                
                // START OF ADD BLOCK
                activityType = getActivityType(false);
                if (activityType == 'h') {
                    if (homeArrayCount < 64) {
                        homeArray[homeArrayCount] = newHomeActivity();
                        homeArrayCount ++;
                    } else {
                        System.out.println("Home Activity Array is Full! Sorry!");
                    }
                } else if (activityType == 's') {
                    if (schoolArrayCount < 64) {
                        schoolArray[schoolArrayCount] = newSchoolActivity();
                        schoolArrayCount ++;
                    } else {
                        System.out.println("School Activity Array is Full! Sorry!");
                    }
                } else if (activityType == 'o') {
                    if (otherArrayCount < 64) {
                        otherArray[otherArrayCount] = newOtherActivity();
                        otherArrayCount ++;
                    } else {
                        System.out.println("Other Activity Array is Full! Sorry!");
                    }
                }
                // END OF ADD BLOCK
                
            } else if (choice == 's') {
                
                // START OF SEARCH BLOCK
                System.out.println("Please input your keywords, seperated by spaces, or press enter to skip keyword search\n>");
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
                
                
                if (activityType == '\n' || activityType == 'h') {
                    System.out.println("\nHome Activity Results:");
                    for(i = 0; i < homeArrayCount; i++) {
                        toPrint = true;
                        if (!(keywords.equals("\n"))) {
                            toPrint = homeArray[i].matchesKeywords(keywords);
                        }
                        if (timeSearch == 'y') {
                            toPrint = homeArray[i].inTimeRange(startTime, endTime);
                        }
                        if (toPrint) {
                            System.out.printf("%s\n",homeArray[i].toString());
                        }
                    }
                }
                if (activityType == '\n' || activityType == 's') {
                    System.out.println("\nSchool Activity Results:");
                    for(i = 0; i < schoolArrayCount; i++) {
                        toPrint = true;
                        if (!(keywords.equals("\n"))) {
                            toPrint = schoolArray[i].matchesKeywords(keywords);
                        }
                        if (timeSearch == 'y') {
                            toPrint = schoolArray[i].inTimeRange(startTime, endTime);
                        }
                        if (toPrint) {
                            System.out.printf("%s\n",schoolArray[i].toString());
                        }
                    }
                }
                if (activityType == '\n' || activityType == 'o') {
                    System.out.println("\nOther Activity Results:");
                    for(i = 0; i < otherArrayCount; i++) {
                        toPrint = true;
                        if (!(keywords.equals("\n"))) {
                            toPrint = otherArray[i].matchesKeywords(keywords);
                        }
                        if (timeSearch == 'y') {
                            toPrint = otherArray[i].inTimeRange(startTime, endTime);
                        }
                        if (toPrint) {
                            System.out.printf("%s\n",otherArray[i].toString());
                        }
                    }
                }
                
                // END OF SEARCH BLOCK
                
            }
            
        } while (choice != 'q');
        
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
}
