/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430_dayplanner;

/**
 * This class is meant to hold date and time as well as date and time 
 * comparison methods.
 * 
 * @author Kyle Hersey, 0851973
 */
public class Time {
    
    private int year;
    private int month;
    private int day;
    private int hour;
    private int minute;
    
    /**
     * Default constructor for Time class;
     */
    public Time() {
        year = -1;
        month = -1;
        day = -1;
        hour = -1;
        minute = -1;
    }
    
    /**
     * Constructor for Time class where every variable is a parameter.
     * 
     * @param year integer representing the year.
     * @param month integer representing the month (range 1-12).
     * @param day integer representing the day (range 1-31)
     * @param hour integer representing the hour (range 0-23)
     * @param minute integer representing the minute (range 0-59)
     */
    public Time(int year, int month, int day, int hour, int minute) {
        this.year = year;
        this.month = month;
        this.day = day;
        this.hour = hour;
        this.minute = minute;
    }
    
    /**
     * Compares this Time class to a different otherTime Time class.
     * 
     * @param otherTime a different Time class
     * @return boolean whether or not the two classes are equal
     */
    public boolean equals(Time otherTime) {
        if (otherTime == null) {
            return false;
        } else {
            return year == otherTime.year 
                    && month == otherTime.month
                    && day == otherTime.day
                    && hour == otherTime.hour
                    && minute == otherTime.minute;
        }
    }
    
    /**
     * Takes the values of year, month, day, hour, and minute, and returns them all
     * as a string.
     * 
     * @return a string value of the class
     */
    @Override
    public String toString() {
        String outStr = String.format("%02d/%02d/%04d %02d:%02d", day,month,year,hour,minute);
        return outStr;
    }
    
    /**
     * Compares two Time classes and returns an integer based on the differences
     * between the two classes. 
     * <br>
     * Returns 1 if the first Time comes after the otherTime Time class.
     * <br>
     * Returns 0 if both Time classes contain the same date.
     * <br>
     * Returns -1 if the first Time comes before the otherTime Time class.
     * 
     * @param otherTime another different Time class
     * @return an integer representing the difference in date between this Time class
     * and the otherTime Time class
     */
    public int compareTo(Time otherTime) {
        //Check year
        if (year > otherTime.year) {
            return 1;
        } else if (year < otherTime.year) {
            return -1;
        } else {    
            //Check month
            if (month > otherTime.month) {
                return 1;
            } else if(month < otherTime.month) {
                return -1;
            } else {    
                //Check day
                if (day > otherTime.day) {
                    return 1;
                } else if (day < otherTime.day) {
                    return -1;
                } else {    
                    //Check hours
                    if (hour > otherTime.hour) {
                        return 1;
                    } else if (hour < otherTime.hour) {
                        return -1;
                    } else { 
                        //check minute
                        if (minute > otherTime.minute) {
                            return 1;
                        } else if (minute < otherTime.minute) {
                            return -1;
                        } else {
                            //if equal return 0
                            return 0;
                        }
                    }
                }
            }
        }
    }
    
    
    
}
