/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430_dayplanner;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

/**
 *
 * @author kyle
 */
public class AddFrame extends JPanel implements ActionListener {
    
    private final GridBagConstraints gbc, gbcParent;
    private JLabel locationLabel;
    private JTextField titleField, locationField, startTimeField, endTimeField, commentField;
    private JTextArea messageArea;
    private JComboBox typeComboBox;
    private final String[] ACTIVITY_TYPES = { "School", "Home", "Other" };
    
    /**
     * Constructor for the GUI Panel which controls adding new activities.
     * 
     */
    public AddFrame() {
        this.setLayout(new GridBagLayout());
        gbcParent = new GridBagConstraints();
        gbcParent.fill = GridBagConstraints.HORIZONTAL;
        
        JPanel inputPanel = new JPanel();
        inputPanel.setLayout(new GridBagLayout());
        gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;
        
        JLabel addLabel = new JLabel("ADD NEW ACTIVITIES");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 1;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 0;
        gbc.gridy = 0;
        inputPanel.add(addLabel, gbc);
        
        JLabel typeLabel = new JLabel("Type: ");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.3;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 0;
        gbc.gridy = 1;
        inputPanel.add(typeLabel, gbc);
        
        typeComboBox = new JComboBox(ACTIVITY_TYPES);
        typeComboBox.setSelectedIndex(0);
        typeComboBox.addActionListener((ActionEvent e) -> {
            if (typeComboBox.getSelectedItem().equals("Other")) {
                locationLabel.setVisible(true);
                locationField.setVisible(true);
            } else {
                locationLabel.setVisible(false);
                locationField.setVisible(false);
            }
        });
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.7;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 1;
        gbc.gridy = 1;
        inputPanel.add(typeComboBox, gbc);
        
        JLabel titleLabel = new JLabel("Title: ");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(5,5,0,0);
        gbc.weightx = 0.3;
        gbc.gridx = 0;
        gbc.gridy = 2;
        inputPanel.add(titleLabel, gbc);
        
        titleField = new JTextField(15);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.7;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 1;
        gbc.gridy = 2;
        inputPanel.add(titleField, gbc);
        
        JLabel timeFormatLabel = new JLabel("Time Format: yyyy MM dd mm hh");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(5,5,0,0);
        gbc.weightx = 0.0;
        gbc.gridwidth = 2;
        gbc.gridx = 0;
        gbc.gridy = 3;
        inputPanel.add(timeFormatLabel, gbc);
        
        JLabel startTimeLabel = new JLabel("Start Time: ");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.3;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 0;
        gbc.gridy = 4;
        inputPanel.add(startTimeLabel, gbc);
        
        startTimeField = new JTextField(15);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.7;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 1;
        gbc.gridy = 4;
        inputPanel.add(startTimeField, gbc);
        
        JLabel endTimeLabel = new JLabel("End Time: ");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.3;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 0;
        gbc.gridy = 5;
        inputPanel.add(endTimeLabel, gbc);
        
        endTimeField = new JTextField(15);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.7;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 1;
        gbc.gridy = 5;
        inputPanel.add(endTimeField, gbc);
        
        locationLabel = new JLabel("Location: ");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.3;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 0;
        gbc.gridy = 6;
        locationLabel.setVisible(false);
        inputPanel.add(locationLabel, gbc);
        
        locationField = new JTextField(15);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.7;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 1;
        gbc.gridy = 6;
        locationField.setVisible(false);
        inputPanel.add(locationField, gbc);
        
        JLabel commentLabel = new JLabel("Comment: ");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.3;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 0;
        gbc.gridy = 7;
        inputPanel.add(commentLabel, gbc);
        
        commentField = new JTextField(15);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.7;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 1;
        gbc.gridy = 7;
        inputPanel.add(commentField, gbc);
        
        
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.PAGE_AXIS));
        
        
        JButton enterButton = new JButton("Enter");
        enterButton.addActionListener((ActionEvent e) -> {
            this.addItem();
        });
        buttonPanel.add(enterButton);
        
        buttonPanel.add(Box.createRigidArea(new Dimension(10,10)));
        
        JButton resetButton =  new JButton("Reset");
        resetButton.addActionListener((ActionEvent e) -> {
            titleField.setText("");
            startTimeField.setText("");
            endTimeField.setText("");
            locationField.setText("");
            commentField.setText("");
        });
        buttonPanel.add(resetButton);
        
        JPanel messagePanel = new JPanel();
        messagePanel.setLayout(new BorderLayout());
        
        messageArea = new JTextArea(15,15);
        messagePanel.add(messageArea, BorderLayout.CENTER);
        
        JScrollPane scroll = new JScrollPane(messageArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        messagePanel.add(scroll);
        
        gbcParent.fill = GridBagConstraints.HORIZONTAL;
        gbcParent.weightx = 1;
        gbcParent.weighty = 0;
        gbcParent.insets = new Insets(0,5,5,5);
        gbcParent.gridx = 0;
        gbcParent.gridy = 0;
        this.add(inputPanel, gbcParent);
        
        gbcParent.fill = GridBagConstraints.HORIZONTAL;
        gbcParent.weightx = 0;
        gbcParent.weighty = 0;
        gbcParent.insets = new Insets(0,0,5,5);
        gbcParent.gridx = 1;
        gbcParent.gridy = 0;
        this.add(buttonPanel, gbcParent);
        
        gbcParent.fill = GridBagConstraints.HORIZONTAL;
        gbcParent.weightx = 0.5;
        gbcParent.weighty = 1;
        gbcParent.insets = new Insets(5,5,5,5);
        gbcParent.gridwidth = 2;
        gbcParent.gridx = 0;
        gbcParent.gridy = 1;
        this.add(messagePanel, gbcParent);
    }
    
    /**
     * If all text fields are found to be valid, this will create a new Activity
     * and pass it to the appropriate addActivity function.
     */
    public void addItem() {
        Time startTime;
        Time endTime;
        
        messageArea.setText("");
        
        if(this.checkFields()) {
            
            startTime = new Time(startTimeField.getText());
            endTime = new Time(endTimeField.getText());
            if(typeComboBox.getSelectedItem().equals("School")) {
                DayPlanner.addSchoolActivity(new SchoolActivity(titleField.getText(),startTime,endTime,commentField.getText()));
            } else if (typeComboBox.getSelectedItem().equals("Home")) {
                DayPlanner.addHomeActivity(new HomeActivity(titleField.getText(),startTime,endTime,commentField.getText()));
            } else if (typeComboBox.getSelectedItem().equals("Other")) {
                DayPlanner.addOtherActivity(new OtherActivity(titleField.getText(),startTime,endTime,commentField.getText(),locationField.getText()));
            }
            titleField.setText("");
            startTimeField.setText("");
            endTimeField.setText("");
            locationField.setText("");
            commentField.setText("");
            messageArea.append("SUCCESS: new activity added!\n");
        }
    }
    
    /**
     * Checks to ensure that the title is not empty, and that the user has 
     * input valid start and end time, and location is not empty should "Other"
     * be the selected Activity type.  Returns true if all conditions are met, 
     * and false if any are not.
     * 
     * @return boolean: true if input is valid, false if it is not.
     */
    public boolean checkFields() {
        boolean title, start, end, location;
        title = !titleField.getText().equals("");
        start = Time.validateTime(startTimeField.getText());
        end  = Time.validateTime(endTimeField.getText());
        location = !locationField.getText().equals("");
        
        if (typeComboBox.getSelectedItem().equals("Other")) {
            if (!title) {
                messageArea.append("ERROR: must have a title\n");
                return false;
            } else if (!start) {
                messageArea.append("ERROR: invalid starting time\n");
                return false;
            } else if (!end) {
                messageArea.append("ERROR: invalid endiung time\n");
                return false;
            } else if (!location) {
                messageArea.append("ERROR: must have a location\n");
                return false;
            } else {
                return true;
            }
        } else {
            if (!title) {
                messageArea.append("ERROR: must have a title\n");
                return false;
            } else if (!start) {
                messageArea.append("ERROR: invalid starting time\n");
                return false;
            } else if (!end) {
                messageArea.append("ERROR: invalid endiung time\n");
                return false;
            } else {
                return true;
            }
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
