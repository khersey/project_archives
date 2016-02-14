/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430_dayplanner;


/**
 * This class holds an activity occurring at school, with a title, start time, end
 * time and comment.
 * 
 * @author Kyle Hersey, 0851973
 */
public class SchoolActivity extends Activity{

    
    /**
     * default constructor for SchoolActivity
     */
    public SchoolActivity () {
        super();
    }
    
    /**
     * constructs a SchoolActivity using the provided variables.
     * 
     * @param title String containing the title of the activity
     * @param startTime Time class holding the starting date and time of the activity.
     * @param endTime Time class holding the ending date and time of the activity.
     * @param comment String holding a comment about the activity.
     */
    public SchoolActivity (String title, Time startTime, Time endTime, String comment) {
        super(title, startTime, endTime, comment);
    }
    
    /**
     * Compares two SchoolActivity classes and returns true if they are the same.
     * 
     * @param obj a different SchoolActivity class.
     * @return a boolean value, true if two classes are equal, false if they are not.
     */
    @Override
    public boolean equals (Object obj) {
        if (obj instanceof SchoolActivity) {
             return super.equals(obj);
        } else {
           return false;
        }
    }
    
    /**
     * Returns the value of all the variables in the class as a String
     * 
     * @return the String value of the class.
     */
    @Override
    public String toString() {
        return "type=school" + "\ntitle=" + title + "\nstartTime=" + startTime.toString() + "\nendTime=" + endTime.toString() + "\ncomment=" + comment +"\n";
    }
    
    /**
     * Returns the value of all the variables in the class as a String
     * but formatted more nicely than toString().  This will be presented
     * to the user.
     * 
     * @return the String value of the class.
     */
    public String printActivity() {
        return "School Activity:\n" + title + "\n" + "Start: " + startTime.printTime() + "\n" + "End:   " + endTime.printTime() + "\n" + "comment: " + comment + "\n";
    }
    
}
