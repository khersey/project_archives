/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430_dayplanner;

/**
 * Class which holds an Activity.
 * @author kyle
 */
public class Activity {
    
    protected String title;
    protected Time startTime;
    protected Time endTime;
    protected String comment;
    
    /**
     * Default constructor for Activity.
     */
    public Activity() {
        title = "unknown activity";
        startTime = new Time();
        endTime = new Time();
        comment = "no comment";
    }    
    
    /**
     * constructs an Activity using the provided variables.
     * 
     * @param title String containing the title of the activity
     * @param startTime Time class holding the starting date and time of the activity.
     * @param endTime Time class holding the ending date and time of the activity.
     * @param comment String holding a comment about the activity.
     */
    public Activity(String title, Time startTime, Time endTime, String comment) {
        this.title = title;
        this.startTime = startTime;
        this.endTime = endTime;
        this.comment = comment;
    }
    
    /**
     * Compares two Activity classes and returns true if they are the same.
     * 
     * @param obj a different Activity class.
     * @return a boolean value, true if two classes are equal, false if they are not.
     */
    @Override 
    public boolean equals(Object obj) {
        if (obj instanceof Activity) {
             return title.equals(((Activity)obj).title)
                    && startTime == ((Activity)obj).startTime
                    && endTime == ((Activity)obj).endTime
                    && comment.equals(((Activity)obj).comment);
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
        return "Activity{" + "title=" + title + ", startTime=" + startTime + ", endTime=" + endTime + ", comment=" + comment + '}';
    }
    
    /**
     * Returns the value of all the variables in the class as a String
     * but formatted more nicely than toString().  This will be presented
     * to the user.
     * 
     * @return the String value of the class.
     */
    public String printActivity() {
        return "Activity:\n" + title + "\n" + "Start: " + startTime.printTime() + "\n" + "End:   " + endTime.printTime() + "\n" + "comment: " + comment + "\n";
    }
    
    /**
     * Checks to see if an Activity's start and end Time fall into the range
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
     * Accessor for member title.
     * @return String title
     */
    public String getTitle() {
        return title;
    }
    
    /**
     * Mutator for member title.
     * @param title New title.
     */
    public void setTitle(String title) {
        this.title = title;
    }

    /**
     * Accessor for member startTime,
     * @return Time startTime
     */
    public Time getStartTime() {
        return startTime;
    }

    /**
     * Mutator for member startTime.
     * @param startTime new startTime
     */
    public void setStartTime(Time startTime) {
        this.startTime = startTime;
    }

    /**
     * Accessor for member endTime.
     * @return Time endTime
     */
    public Time getEndTime() {
        return endTime;
    }

    /**
     * Mutator for member endTime.
     * @param endTime new endTime
     */
    public void setEndTime(Time endTime) {
        this.endTime = endTime;
    }

    /**
     * Accessor for member comment.
     * @return String comment
     */
    public String getComment() {
        return comment;
    }

    /**
     * Mutator for member comment.
     * @param comment new comment
     */
    public void setComment(String comment) {
        this.comment = comment;
    }
    
}
