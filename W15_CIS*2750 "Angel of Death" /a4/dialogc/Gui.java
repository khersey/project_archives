package dialogc;


import javax.swing.*;
import javax.swing.JScrollPane;
import javax.swing.JToolBar;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.filechooser.FileFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.*;

/**
 * This class creates and displays the User Inteface.
 */
public class Gui extends javax.swing.JFrame implements ActionListener {
    private JTextArea ide;
    private JLabel labelFileName;
    private JTextField fieldStatus;
    private Settings settings;
    private boolean modified;

    public Gui() {
        super("Dialogc");
        setSize(800, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        settings = new Settings();
        init();
    }

    /*
    This function initializes the GUI.
     */
    private void init() {
        initMenu();
        initToolbar();
        initWindowListener();
        modified = false;


        JPanel basePanel = new JPanel(new BorderLayout());

        ide = new JTextArea(15,15);
        ide.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                fieldStatus.setText("Current Project: " + settings.getFilename() + " [modified]");
                modified = true;
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                fieldStatus.setText("Current Project: " + settings.getFilename() + " [modified]");
                modified = true;
            }

            @Override
            public void changedUpdate(DocumentEvent e) {

            }
        });
        JScrollPane scroll = new JScrollPane(ide, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        basePanel.add(scroll, BorderLayout.CENTER);

        labelFileName = new JLabel("   " + settings.getFilename());
        basePanel.add(labelFileName, BorderLayout.NORTH);

        fieldStatus =  new JTextField("Current Project: " + settings.getFilename());
        fieldStatus.setEditable(false);
        basePanel.add(fieldStatus, BorderLayout.SOUTH);

        this.add(basePanel, BorderLayout.CENTER);
    }

    /*
    This function initializes the GUI's menu and actions performed when menu items are clicked.
     */
    private void initMenu() {

        JMenuBar menuBar = new JMenuBar();


        JMenu menu_file = new JMenu("File");

        JMenuItem file_new = new JMenuItem("New");
        file_new.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                newProject();
            }
        });
        file_new.setMnemonic('N');
        menu_file.add(file_new);

        JMenuItem file_open = new JMenuItem("Open");
        file_open.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                open();
            }
        });
        file_open.setMnemonic('O');
        menu_file.add(file_open);

        JMenuItem file_save = new JMenuItem("Save");
        file_save.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                save();
            }
        });
        file_save.setMnemonic('S');
        menu_file.add(file_save);

        JMenuItem file_saveAs = new JMenuItem("Save As");
        file_saveAs.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                saveAs();
            }
        });
        file_saveAs.setMnemonic('A');
        menu_file.add(file_saveAs);

        JMenuItem file_quit = new JMenuItem("Quit");
        file_quit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                quit();
            }
        });
        file_quit.setMnemonic('Q');
        menu_file.add(file_quit);

        menu_file.setMnemonic('F');
        menuBar.add(menu_file);


        JMenu menu_compile = new JMenu("Compile");

        JMenuItem compile_compile = new JMenuItem("Compile");
        compile_compile.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                compile();
            }
        });
        compile_compile.setMnemonic('C');
        menu_compile.add(compile_compile);

        JMenuItem compile_compileAndRun = new JMenuItem("Compile and Run");
        compile_compileAndRun.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                compileRun();
            }
        });
        compile_compileAndRun.setMnemonic('R');
        menu_compile.add(compile_compileAndRun);

        menu_compile.setMnemonic('C');
        menuBar.add(menu_compile);


        JMenu menu_config = new JMenu("Config");

        ButtonGroup radioGroup = new ButtonGroup();
        JMenu submenu_compileMode = new JMenu("Compile Mode");
        final JRadioButtonMenuItem internal_compileMode = new JRadioButtonMenuItem("Use IDE", true);
        internal_compileMode.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                if(internal_compileMode.isSelected()) {
                    settings.setUseYadc(false);
                }
            }
        });
        radioGroup.add(internal_compileMode);
        submenu_compileMode.add(internal_compileMode);
        final JRadioButtonMenuItem external_compileMode = new JRadioButtonMenuItem("Use YADC",false);
        external_compileMode.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent e) {
                if(external_compileMode.isSelected()) {
                    settings.setUseYadc(true);
                }
            }
        });
        radioGroup.add(external_compileMode);
        submenu_compileMode.add(external_compileMode);
        submenu_compileMode.setMnemonic('M');
        menu_config.add(submenu_compileMode);

        JMenu submenu_jCompiler = new JMenu("Java Compiler");
        final JMenuItem config_jCompiler = new JMenuItem(settings.getCompiler());
        config_jCompiler.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String newPath = JOptionPane.showInputDialog(ide, "Enter Path of New Java Compiler");
                if(!newPath.equals("") && newPath != null) {
                    settings.setCompiler(newPath);
                    config_jCompiler.setText(settings.getCompiler());
                }
            }
        });
        submenu_jCompiler.add(config_jCompiler);
        JMenuItem jCompiler_browse = new JMenuItem("Browse");
        jCompiler_browse.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
                chooser.setDialogTitle("Select Java Compiler");
                int result = chooser.showOpenDialog(ide);
                if(result == JFileChooser.APPROVE_OPTION) {
                    File compiler = chooser.getSelectedFile();
                    settings.setCompiler(compiler.getAbsolutePath());
                    config_jCompiler.setText(settings.getCompiler());
                }
            }
        });
        submenu_jCompiler.add(jCompiler_browse);
        submenu_jCompiler.setMnemonic('C');
        menu_config.add(submenu_jCompiler);

        JMenu submenu_compileOptions = new JMenu("Compile Options");
        final JMenuItem config_compileOptions = new JMenuItem("args: " + settings.getCompilerArgs());
        config_compileOptions.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String newArgs = JOptionPane.showInputDialog(ide, "Enter New Arguments");
                if(!newArgs.equals("") && newArgs != null) {
                    settings.setCompilerArgs(newArgs);
                    config_compileOptions.setText(settings.getCompilerArgs());
                }
            }
        });
        submenu_compileOptions.add(config_compileOptions);
        submenu_compileOptions.setMnemonic('O');
        menu_config.add(submenu_compileOptions);

        JMenu submenu_jvm = new JMenu("Java Run-Time");
        final JMenuItem config_jvm = new JMenuItem(settings.getJVM());
        config_jvm.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String newPath = JOptionPane.showInputDialog(ide, "Enter Path of New Java Runtime Environment");
                if(!newPath.equals("") && newPath != null) {
                    settings.setJVM(newPath);
                    config_jvm.setText(settings.getJVM());
                }
            }
        });
        submenu_jvm.add(config_jvm);
        JMenuItem jvm_browse = new JMenuItem("Browse");
        jvm_browse.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
                chooser.setDialogTitle("Select Java Runtime Environment");
                int result = chooser.showOpenDialog(ide);
                if(result == JFileChooser.APPROVE_OPTION) {
                    File compiler = chooser.getSelectedFile();
                    settings.setJVM(compiler.getAbsolutePath());
                    config_jvm.setText(settings.getJVM());
                }
            }
        });
        submenu_jvm.add(jvm_browse);
        submenu_jvm.setMnemonic('T');
        menu_config.add(submenu_jvm);

        JMenu submenu_jvmOptions = new JMenu("Run-time Options");
        final JMenuItem config_jvmOptions = new JMenuItem("args: " + settings.getJVMArgs());
        config_jvmOptions.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String newArgs = JOptionPane.showInputDialog(ide, "Enter New Arguments");
                if(!newArgs.equals("") && newArgs != null) {
                    settings.setJVMArgs(newArgs);
                    config_jvmOptions.setText(settings.getJVMArgs());
                }
            }
        });
        submenu_jvmOptions.add(config_jvmOptions);
        submenu_jvmOptions.setMnemonic('R');
        menu_config.add(submenu_jvmOptions);

        JMenu submenu_directory = new JMenu("Working Directory");
        final JMenuItem config_directory = new JMenuItem(settings.getWorkingDir());
        config_directory.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String newArgs = JOptionPane.showInputDialog(ide, "Enter Working Directory");
                if(!newArgs.equals("") && newArgs != null) {
                    settings.setWorkingDir(newArgs);
                    config_directory.setText(settings.getWorkingDir());
                }
            }
        });
        submenu_directory.add(config_directory);
        JMenuItem directory_browse = new JMenuItem("Browse");
        directory_browse.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                chooser.setDialogTitle("Select Working Directory");
                int result = chooser.showOpenDialog(ide);
                if(result == JFileChooser.APPROVE_OPTION) {
                    File directory = chooser.getSelectedFile();
                    settings.setWorkingDir(directory.getAbsolutePath());
                    config_directory.setText(settings.getWorkingDir());
                }
            }
        });
        submenu_directory.add(directory_browse);
        submenu_directory.setMnemonic('D');
        menu_config.add(submenu_directory);
        menu_config.setMnemonic('G');

        menuBar.add(menu_config);

        JMenu menu_help = new JMenu("Help");
        JMenuItem help_help = new JMenuItem("Help");
        help_help.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JTextArea logArea = new JTextArea(6,25);
                logArea.setText("Dialog Compiler\n" +
                        "Please set Compiler and JRE/JVM before using Compile and Run\n" +
                        "In order for javac to compile source code correctly classpath must be provided\n"
                );
                logArea.setEditable(false);
                JScrollPane scroll = new JScrollPane(logArea);
                JOptionPane.showMessageDialog((Component)null, scroll);
            }
        });
        help_help.setMnemonic('H');
        menu_help.add(help_help);

        JMenuItem help_about = new JMenuItem("About");
        help_about.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JTextArea logArea = new JTextArea(6,25);
                logArea.setText("Author: Kyle Hersey\nStudent Number: 0851973\nAssignment 2 for CIS*2750\n");
                logArea.setEditable(false);
                JOptionPane.showMessageDialog((Component)null, logArea);
            }
        });
        help_about.setMnemonic('A');
        menu_help.add(help_about);
        menu_help.setMnemonic('H');
        menuBar.add(menu_help);

        setJMenuBar(menuBar);
    }

    /*
    This function initializes the GUI's buttonbar and actions perfomed when these buttons are pressed.
     */
    private void initToolbar() {
        JPanel buttonPanel = new JPanel(new GridLayout(1,2));
        JToolBar toolBar = new JToolBar();

        ImageIcon icon_new = new ImageIcon("img/new.png");
        ImageIcon icon_open = new ImageIcon("img/open.png");
        ImageIcon icon_save = new ImageIcon("img/save.png");
        ImageIcon icon_saveAs = new ImageIcon("img/saveAs.png");
        ImageIcon icon_compile = new ImageIcon("img/compile.png");
        ImageIcon icon_compileRun = new ImageIcon("img/compileRun.png");


        JButton button_new = new JButton(icon_new);
        button_new.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                newProject();
            }
        });
        toolBar.add(button_new);

        JButton button_open = new JButton(icon_open);
        button_open.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                open();
            }
        });
        toolBar.add(button_open);

        JButton button_save = new JButton(icon_save);
        button_save.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                save();
            }
        });
        toolBar.add(button_save);

        JButton button_saveAs = new JButton(icon_saveAs);
        button_saveAs.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                saveAs();
            }
        });
        toolBar.add(button_saveAs);

        JButton button_compile = new JButton(icon_compile);
        button_compile.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                compile();
            }
        });
        toolBar.add(button_compile);

        JButton button_compileRun = new JButton(icon_compileRun);
        button_compileRun.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                compileRun();
            }
        });
        toolBar.add(button_compileRun);

        buttonPanel.add(toolBar);
        this.add(buttonPanel, BorderLayout.NORTH);

    }

    private void initWindowListener() {
        this.addWindowListener(new WindowListener() {
            @Override
            public void windowOpened(WindowEvent e) {

            }

            @Override
            public void windowClosing(WindowEvent e) {
                quit();
            }

            @Override
            public void windowClosed(WindowEvent e) {

            }

            @Override
            public void windowIconified(WindowEvent e) {

            }

            @Override
            public void windowDeiconified(WindowEvent e) {

            }

            @Override
            public void windowActivated(WindowEvent e) {

            }

            @Override
            public void windowDeactivated(WindowEvent e) {

            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        //do something
    }

    /*
    ensure the current project is saved, then create a Generator and call generate() to create .java files.
     */
    private void compile() {
        save();
        if(settings.getUseYadc()) {
            compileWithYADC();
        } else {
            Generator gen = new Generator(settings);
            gen.generate();
        }
    }

    private void compileWithYADC() {
        boolean error = false;
        try {
            String arg = "bin/yadc " + settings.getFilepath() + " " + settings.getWorkingDir();
            Runtime runtime = Runtime.getRuntime();
            Process process_javac = runtime.exec(arg);
            InputStream is = process_javac.getInputStream();
            InputStreamReader isr = new InputStreamReader(is);
            BufferedReader br = new BufferedReader(isr);
            String line = br.readLine();
            while(line != null) {
                line = br.readLine();
            }

        } catch (IOException e) {
            error = true;
            JTextArea logArea = new JTextArea(6,25);
            logArea.setText("An Error Occured Compiling!\n" + "\n" + e.getMessage());
            logArea.setEditable(false);
            JScrollPane scroll = new JScrollPane(logArea);
            JOptionPane.showMessageDialog((Component)null, scroll);
        }

        if(error==false) {
            JTextArea logArea = new JTextArea(6,25);
            logArea.setText("Compilation with YADC Complete\n");
            logArea.setEditable(false);
            JScrollPane scroll = new JScrollPane(logArea);
            JOptionPane.showMessageDialog((Component)null, scroll);
        }
    }

    /*
    call compile, and then attempt to compile and run the generated .java files.
     */
    private void compileRun() {
        compile();
        try {
            String arg = settings.getCompiler() + " " + settings.getCompilerArgs() + " " + settings.getWorkingDir() + "/" + settings.getFilename() + " " + settings.getWorkingDir() + "/" + settings.getFilename() + "/" + settings.getFilename() + ".java";
            Runtime runtime = Runtime.getRuntime();
            Process process_javac = runtime.exec(arg);
            InputStream is = process_javac.getErrorStream();
            InputStreamReader isr = new InputStreamReader(is);
            BufferedReader br = new BufferedReader(isr);
            String line = br.readLine();
            while(line != null) {
                line = br.readLine();
            }

        } catch (IOException e) {
            JTextArea logArea = new JTextArea(6,25);
            logArea.setText("An Error Occured Compiling!\n" + "Make sure you set the Compiler and Compiler Arguments\n" + e.getMessage());
            logArea.setEditable(false);
            JScrollPane scroll = new JScrollPane(logArea);
            JOptionPane.showMessageDialog((Component)null, scroll);
        }

        try {
            String arg = settings.getJVM() + " " + settings.getJVMArgs() + " " + settings.getWorkingDir() + "/" + settings.getFilename() + " " + settings.getFilename();
            Runtime runtime = Runtime.getRuntime();
            Process process_java = runtime.exec(arg);
            InputStream is = process_java.getInputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            String line = br.readLine();
            while(line != null) {
                line = br.readLine();
            }
        } catch (IOException e) {
            JTextArea logArea = new JTextArea(6,25);
            logArea.setText("An Error Occured Running!\n" + "Make sure you set the JRE/JVM and Run-Time Arguments\n" + e.getMessage());
            logArea.setEditable(false);
            JScrollPane scroll = new JScrollPane(logArea);
            JOptionPane.showMessageDialog((Component) null, scroll);
        }
    }

    /*
    Select location for config file to be saved, and config file name, before saving config file.
     */
    private void saveAs() {
        JFileChooser chooser = new JFileChooser();
        chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
        chooser.setFileFilter(new FileFilter() {
            @Override
            public boolean accept(File f) {
                if(f.isDirectory()) {
                    return true;
                } else {
                    return f.getName().toLowerCase().endsWith(".config");
                }
            }

            @Override
            public String getDescription() {
                return "*.config";
            }
        });
        chooser.setDialogTitle("Save As");
        int result = chooser.showSaveDialog(ide);
        if(result == JFileChooser.APPROVE_OPTION) {
            File saveMe = chooser.getSelectedFile();
            if(saveMe.getName().endsWith(".config")) {
                settings.setFilename(saveMe.getName());
                labelFileName.setText("   " + settings.getFilename());
                settings.setFilepath(saveMe.getAbsolutePath());
            } else {
                settings.setFilename(saveMe.getName() + ".config");
                labelFileName.setText("   " + settings.getFilename());
                settings.setFilepath(saveMe.getAbsolutePath() + ".config");
            }
            doSave();
        }
    }

    /*
    Write text from ide JTextArea to file.
     */
    private void doSave() {
        PrintWriter writer;
        try {
            writer = new PrintWriter(settings.getFilepath(), "UTF-8");
            writer.printf("%s\n",ide.getText());
            writer.close();
        } catch (IOException e) {
            //process exception
        }
        fieldStatus.setText("Current Project: " + settings.getFilename() + " [saved]");
        modified = false;
    }

    /*
    If current project has never been previously saved call saveAs() otherwise call doSave().
     */
    private void save() {
        if(settings.getFilename().equals("untitled")) {
            saveAs();
        } else {
            doSave();
        }
    }

    /*
    Save current project, then select a new file to open, and print its contents to the ide JTextArea.
     */
    private void open() {
        int save;

        if(modified == true) {
            save = prompt("Save current project before continuing?");
        } else {
            save = JOptionPane.NO_OPTION;
        }

        if(save == JOptionPane.YES_OPTION) {
            save();
        }

        if(save != JOptionPane.CANCEL_OPTION) {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
            chooser.setFileFilter(new FileFilter() {
                @Override
                public boolean accept(File f) {
                    if(f.isDirectory()) {
                        return true;
                    } else {
                        return f.getName().toLowerCase().endsWith(".config");
                    }
                }

                @Override
                public String getDescription() {
                    return "*.config";
                }
            });
            chooser.setDialogTitle("Open a file");
            int result = chooser.showOpenDialog(ide);
            if(result == JFileChooser.APPROVE_OPTION) {
                File saveMe = chooser.getSelectedFile();
                settings.setFilename(saveMe.getName());
                settings.setFilepath(saveMe.getAbsolutePath());
                ide.setText("");
                BufferedReader br;
                try {
                    br = new BufferedReader(new FileReader(settings.getFilepath()));
                    String line = br.readLine();
                    while(line != null) {
                        ide.append(line + "\n");
                        line = br.readLine();
                    }
                    br.close();
                } catch (IOException e) {
                    //handle exception
                }

                updateGUI();
                modified = false;
            }
        }

    }

    /*
    prompt the user to save current project, then wipe ide JTextArea.
     */
    private void newProject() {
        int save;

        if(modified == true) {
            save = prompt("Save current project before continuing?");
        } else {
            save = JOptionPane.NO_OPTION;
        }

        if(save == JOptionPane.YES_OPTION) {
            save();
        }

        if(save != JOptionPane.CANCEL_OPTION) {
            settings.setFilename("untitled.config");
            settings.setFilepath("/");
            ide.setText("");
            updateGUI();
        }
    }

    /*
    prompt to save current project and then exit.
     */
    private void quit() {
        int save;

        if(modified == true) {
            save = prompt("Save current project before exiting?");
        } else {
            save = JOptionPane.NO_OPTION;
        }

        if(save == JOptionPane.YES_OPTION) {
            save();
        }

        if(save != JOptionPane.CANCEL_OPTION) {
            this.dispose();
            System.exit(1);
        }
    }

    /*
    create pop up window with yes, no and cancel options.
     */
    private int prompt(String question) {
        int result = JOptionPane.showConfirmDialog((Component)null, question, "alert", JOptionPane.YES_NO_CANCEL_OPTION);
        return result;
    }

    /*
    updates both fields dependant on the current open filename in the GUI.
     */
    private void updateGUI() {
        labelFileName.setText("   " + settings.getFilename() + ".config");
        fieldStatus.setText("Current Project: " + settings.getFilename());
    }
}
