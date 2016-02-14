/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430_dayplanner;

import java.util.StringTokenizer;

/**
 * This class holds an activity occurring at school, with a title, start time, end
 * time and comment.
 * 
 * @author Kyle Hersey, 0851973
 */
public class SchoolActivity {
    
    private String title;
    private Time startTime;
    private Time endTime;
    private String comment;
    
    /**
     * default constructor for SchoolActivity
     */
    public SchoolActivity () {
        title = "unknown activity";
        startTime = new Time();
        endTime = new Time();
        comment = "no comment";
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
        this.title = title;
        this.startTime = startTime;
        this.endTime = endTime;
        this.comment = comment;
    }
    
    /**
     * Compares two SchoolActivity classes and returns true if they are the same.
     * 
     * @param notThis a different SchoolActivity class.
     * @return a boolean value, true if two classes are equal, false if they are not.
     */
    public boolean equals (SchoolActivity notThis) {
        if (notThis == null) {
            return false;
        } else {
            return title.toLowerCase().equals(notThis.title)
                    && startTime == notThis.startTime
                    && endTime == notThis.endTime
                    && comment.equals(notThis.comment);
        }
    }
    
    /**
     * Checks to see if the keywords in the passed String input exactly match 
     * the title of this class.  This involves tokenizing both Strings, and 
     * comparing each token to each other.  In order for true to be returned 
     * every single token in the passed String must match a token in the title.
     * 
     * @param input a String containing keywords separated by a space.
     * @return a boolean value containing the result of a keyword comparison.
     */
    public boolean matchesKeywords(String input) {
        String keywords = input, keyTok;
        String titlewords = title.toLowerCase(), titleTok;
        boolean matches;
        StringTokenizer kt = new StringTokenizer(keywords);
        StringTokenizer tt;
        
        while(kt.hasMoreTokens()) {
            keyTok = kt.nextToken();
            tt = new StringTokenizer(titlewords);
            matches = false;
            while(tt.hasMoreTokens()) {
                titleTok = tt.nextToken();
                if (titleTok.equals(keyTok)) {
                    matches = true;
                }
            }
            if(!matches) {
                return false;
            }
        }
        return true;
    }
    
    /**
     * Checks to see if this HomeActivity's start and end Time fall into the range
     * of the passed start and end Times, returning true if they do.
     * 
     * @param startRange the start Time of a range of time.
     * @param endRange the end Time of a range of time.
     * @return boolean whether or not the start and end time fall within the given times.
     */
    public boolean inTimeRange(Time startRange, Time endRange) {
        if(startTime.compareTo(startRange) >= 0 && endTime.compareTo(endRange) <= 0) {
            return true;
        } else{
            return false;
        }
    }
    /**
     * Returns the title of the HomeActivity.
     * 
     * @return title of the activity as a String.
     */
    public String getTitle() {
        return title;
    }
    
    /**
     * Returns the starting Time of the activity.
     * 
     * @return the starting Time of the activity
     */
    public Time getStartTime() {
        return startTime;
    }
    
    /**
     * Returns the ending Time of the activity.
     * 
     * @return the ending Time of the activity.
     */
    public Time getEndTime() {
        return endTime;
    }
    
    /**
     * Returns the value of all the variables in the class as a String
     * 
     * @return the String value of the class.
     */
    @Override public String toString() {
        String outStr = String.format("Title: %s\nStart Time: %s\nEnd Time: %s\nComment: %s\n",
                title,startTime.toString(),endTime.toString(),comment);
        return outStr;
    }
}
