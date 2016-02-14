/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430_dayplanner;

import java.awt.CardLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import javax.swing.*;

/**
 *
 * @author kyle
 */
public class GUI extends JFrame implements ActionListener {
    
    private JPanel basePanel, welcomePanel;
    private SearchFrame search;
    private AddFrame add;
    
    
    /**
     * Constructor for GUI class. 
     */
    public GUI() {
        super("Day Planner");
        setSize(465,550);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        addWindowListener(new CheckOnExit() {});
        basePanel = new JPanel(new CardLayout());
        init();
        
        
        basePanel.setVisible(true);
        add(basePanel);
    }
    
    /**
     * Creates and adds all visual elements to the GUI.
     * 
     */
    private void init() {
        initMenu();
        initWelcome();
        search = new SearchFrame();
        search.setVisible(true);
        basePanel.add(search, "Search");
        add    = new AddFrame();
        add.setVisible(true);
        basePanel.add(add, "Add");
        this.changeState("Welcome");
        
    }
    
    /**
     * Creates the Welcome JPanel and adds it to the basePanel.
     */
    private void initWelcome() {
        welcomePanel = new JPanel();
        welcomePanel.setLayout(new BoxLayout(welcomePanel, BoxLayout.PAGE_AXIS));
        welcomePanel.setBorder(BorderFactory.createEmptyBorder(30, 30, 30, 30));
        
        JLabel welcomeLabel = new JLabel("Welcome to Kyle Hersey's Day Planer");
        welcomePanel.add(welcomeLabel);
        
        welcomePanel.add(Box.createRigidArea(new Dimension(10,10)));
        
        JLabel welcomeLabel2 = new JLabel("Add and Search Activies, or Quit, from the Commands menu");
        welcomePanel.add(welcomeLabel2);
        
        welcomePanel.setVisible(true);
        basePanel.add(welcomePanel, "Welcome");
    }
    
    /**
     * Creates the menu/menu bar that appears at the top of the GUI.
     */
    private void initMenu() {
        
        JMenuBar menuBar = new JMenuBar();
        
        JMenu commands = new JMenu("Commands");
        
        JMenuItem add = new JMenuItem("Add");
        add.addActionListener((ActionEvent e) -> {
            changeState("Add");
        });
        commands.add(add);
        
        JMenuItem search = new JMenuItem("Search");
        search.addActionListener((ActionEvent e) -> {
            changeState("Search");
        });
        commands.add(search);
        
        JMenuItem quit = new JMenuItem("Quit");
        quit.addActionListener((ActionEvent e) -> {
            System.out.println("QUITING");
            System.exit(0);
        });
        commands.add(quit);
        
        menuBar.add(commands);
        
        setJMenuBar(menuBar);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    /**
     * Ensures that the program exits when the window is closed.
     */
    private abstract class CheckOnExit implements WindowListener {
        
        public void windowOpened (WindowEvent e) {}
        
        public void windowClosing (WindowEvent e) {
            dispose();
            System.exit(0);
        }
        
        public void windowClosed (WindowEvent e) {}
        
        public void windowIconified (WindowEvent e) {}
        
        public void windowDeiconified (WindowEvent e) {}
        
        public void windowActivated (WindowEvent e) {}
        
        public void windowDeactivated (WindowEvent e) {}
        
    }
    
    /**
     * Controls the current card being displayed by the CardLayout.
     * @param state String name of the new card to be shown.
     */
    public void changeState(String state) {
        CardLayout cl = (CardLayout)(basePanel.getLayout());
        cl.show(basePanel, state);
    }
    
}
