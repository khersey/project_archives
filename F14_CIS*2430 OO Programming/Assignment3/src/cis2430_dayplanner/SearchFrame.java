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
public class SearchFrame extends JPanel implements ActionListener {
    
    private final String[] ACTIVITY_TYPES = { "School", "Home", "Other" , "All" };
    private final GridBagConstraints gbcParent, gbc;
    private final JTextArea messageArea;
    private JTextField titleField, startTimeField, endTimeField;
    private final JComboBox typeComboBox;
    
    /**
     * Constructor for the GUI Panel which search existing activities.
     */
    public SearchFrame() {
        
        this.setLayout(new GridBagLayout());
        gbcParent = new GridBagConstraints();
        gbcParent.fill = GridBagConstraints.HORIZONTAL;
        
        JPanel inputPanel = new JPanel();
        inputPanel.setLayout(new GridBagLayout());
        gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;
        
        JLabel searchLabel = new JLabel("SEARCH FOR ACTIVITIES");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(5,5,0,0);
        gbc.weightx = 0.3;
        gbc.gridx = 0;
        gbc.gridy = 0;
        inputPanel.add(searchLabel, gbc);
        
        JLabel typeLabel = new JLabel("Type: ");
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 0.3;
        gbc.insets = new Insets(5,5,0,0);
        gbc.gridx = 0;
        gbc.gridy = 1;
        inputPanel.add(typeLabel, gbc);
        
        
        typeComboBox = new JComboBox(ACTIVITY_TYPES);
        typeComboBox.setSelectedIndex(0);
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
        
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.PAGE_AXIS));
        
        
        JButton enterButton = new JButton("Enter");
        enterButton.addActionListener((ActionEvent e) -> {
            this.search();
        });
        buttonPanel.add(enterButton);
        
        buttonPanel.add(Box.createRigidArea(new Dimension(10,10)));
        
        JButton resetButton =  new JButton("Reset");
        resetButton.addActionListener((ActionEvent e) -> {
            titleField.setText("");
            startTimeField.setText("");
            endTimeField.setText("");
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
     * Executes Search for Activities and prints out all results to the message box.
     */
    private void search() {
        messageArea.setText("");
        Time startTime = null;
        Time endTime = null;
        if (Time.validateTime(startTimeField.getText()) && Time.validateTime(endTimeField.getText())) {
            startTime = new Time(startTimeField.getText());
            endTime = new Time(endTimeField.getText());
        }
        MyArrayList<String> result = DayPlanner.doSearch((String)typeComboBox.getSelectedItem(), titleField.getText(), startTime, endTime);
        for (String str: result) {
            messageArea.append(str );
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    
}
