/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430_dayplanner;


import java.util.ArrayList;

/**
 * Sub-class of ArrayList to add an addElement method to ArrayLists.
 * @author kyle
 * @param <T> Object which will be stored in MyArrayList.
 */
public class MyArrayList<T> extends ArrayList<T>{
    
    /**
     * Adds a new element to MyArrayList, expanding the size of the list by 1
     * if it is full. Provides the same functionality as the Vector method 
     * addElement().
     * @param element object to be added.
     * @return integer containing the position the element was added to in 
     * the MyArrayList.
     */
    public int addElement(T element) {
        this.ensureCapacity(this.size() + 1);
        this.add(element);
        return this.size() - 1;
    }
   
}
