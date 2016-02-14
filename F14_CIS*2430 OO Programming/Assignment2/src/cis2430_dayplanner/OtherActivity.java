/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430_dayplanner;

import java.util.StringTokenizer;

/**
 * This class holds an activity occurring at a location other than home or school,
 * with a title, start time, end time, comment, and location.
 * 
 * @author Kyle Hersey, 0851973
 */
public class OtherActivity extends Activity{
    
    private String location;
    
    /**
     * default constructor for OtherActivity
     */
    public OtherActivity () {
        super();
        location = "nowhere";
    }
    
    /**
     * constructs a OtherActivity using the provided variables.
     * 
     * @param title String containing the title of the activity
     * @param startTime Time class holding the starting date and time of the activity.
     * @param endTime Time class holding the ending date and time of the activity.
     * @param comment String holding a comment about the activity.
     * @param location String holding the location of the activity.
     */
    public OtherActivity (String title, Time startTime, Time endTime, String comment, String location) {
        super(title, startTime, endTime, comment);
        this.location = location;
    }
    
    /**
     * Compares two OtherActivity classes and returns true if they are the same.
     * 
     * @param obj a different OtherActivity class.
     * @return a boolean value, true if two classes are equal, false if they are not.
     */
    @Override
    public boolean equals (Object obj) {
        if (obj instanceof OtherActivity) {
             return super.equals(obj)
                    && location.equals(((OtherActivity)obj).location) ;
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
        return "type=other" + "\ntitle=" + title + "\nstartTime=" + startTime.toString() + "\nendTime=" + endTime.toString() + "\nlocation=" + location + "\ncomment=" + comment + '\n';
    }
    
    /**
     * Returns the value of all the variables in the class as a String
     * but formatted more nicely than toString().  This will be presented
     * to the user.
     * 
     * @return the String value of the class.
     */
    public String printActivity() {
        return "Other Activity:\n" + title + "\n" + "Start: " + startTime.printTime() + "\n" + "End:   " + endTime.printTime() + "\n" + "location: " + location + "\n" + "comment: " + comment + "\n";
    }
    
}
