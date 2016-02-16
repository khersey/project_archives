package dialogc;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * Created by kyle on 15-02-12.
 * This class is responsible for generating and writing java source code
 */
public class Generator {
    private String source;
    private String fieldEdit;
    private Settings settings;

    public Generator(Settings settings) {
        this.settings = settings;
    }

    /*
    This function initializes a PM_Parser directed to the currently opened config file,
    and if it parses successfully passes it to generateSource() and generateFieldEdit.
    This function then writes the generated source code and interface to .java files.
     */
    public void generate() {
        StringBuilder log = new StringBuilder();
        log.append("COMPILATION LOG:\n");
        String compileDir = settings.getWorkingDir() + "/" + settings.getFilename();
        log.append("Attempting to parse: " + settings.getFilename() + ".config\n");

        PM_Parser pmp = new PM_Parser(settings.getFilepath());

        if(pmp.isSuccess()) {
            log.append("parse SUCCESS!\n");
            generateSource(pmp);
            generateFieldEdit(pmp);

            File makeCompileDir = new File(compileDir);
            makeCompileDir.mkdir();

            PrintWriter sourceWriter;

            log.append("Attempting to write source file...\n");
            try {
                sourceWriter = new PrintWriter(compileDir + "/" + settings.getFilename() + ".java", "UTF-8");
                sourceWriter.printf("%s\n", source);
                sourceWriter.close();
            } catch (IOException e) {
                log.append("ERROR: Something went wrong writing source file\n");
            }

            PrintWriter interfaceWriter;
            log.append("Attempting to write interface file...\n");
            try {
                interfaceWriter = new PrintWriter(compileDir + "/" + settings.getFilename() + "FieldEdit.java", "UTF-8");
                interfaceWriter.printf("%s\n", fieldEdit);
                interfaceWriter.close();
            } catch (IOException e) {
                log.append("ERROR: Something went wrong writing interface file\n");
            }
            log.append("Compilation Finished\n");
        } else {
            log.append("Parse FAILURE\n");
            log.append("Aborting...\n");
        }


        JTextArea logArea = new JTextArea(6,25);
        logArea.setText(log.toString());
        logArea.setEditable(false);

        JScrollPane scroll = new JScrollPane(logArea);

        JOptionPane.showMessageDialog((Component)null, scroll);
    }

    /*
    This function takes a PM_Parser object as a parameter and uses the data contained within to generate
    java code to produce a simple GUI.
    */
    public void generateSource(PM_Parser data) {
        StringBuilder sb = new StringBuilder();
        sb.append(
                "import javax.swing.*;" + "\n" +
                "import java.awt.*;" + "\n" +
                "\n" +
                "public class " + settings.getFilename() + " extends JFrame implements " + settings.getFilename() + "FieldEdit {" + "\n"
        );

        for(String s: data.getFieldName()) {
            sb.append("\t" + "private JTextField " + s + ";" + "\n");
        }

        sb.append("\t" + "private JTextArea statusArea;" + "\n\n");

        sb.append("\t" + "public " + settings.getFilename() + " () {" + "\n" +
                "\t\t" + "super(\"" + data.getTitle() + "\");" + "\n" +
                "\t\t" + "setDefaultCloseOperation(EXIT_ON_CLOSE);" + "\n" +
                "\t\t" + "setLayout(new BorderLayout());" + "\n" +
                "\t\t" + "setSize(350,600);" + "\n" +
                "\t\t" + "init();" + "\n" +
                "\t\t" + "pack();" + "\n" +
                "\t\t" + "}" + "\n\n"
        );

        sb.append("\t" + "private void init() {\n" +
                "\t\t" + "JPanel topPanel = new JPanel(new BorderLayout());\n" +
                "\t\t" + "\n" +
                "\t\t" + "JPanel fieldPanel = new JPanel();\n" +
                "\t\t" + "GroupLayout fieldLayout = new GroupLayout(fieldPanel);\n" +
                "\t\t" + "fieldPanel.setLayout(fieldLayout);\n" +
                "\t\t" + "fieldLayout.setAutoCreateGaps(true);\n" +
                "\t\t" + "fieldLayout.setAutoCreateContainerGaps(true);\n" +
                "\n");
        for(String s: data.getFieldName()) {
            sb.append("\t\t" + s + "= new JTextField(15);" + "\n" +
                      "\t\t" + "JLabel label" + s + " = new JLabel(\"" + s +"\");" + "\n"
            );
        }
        sb.append("\n");

        sb.append("\t\t" + "fieldLayout.setHorizontalGroup(" + "\n" +
                "\t\t\t" + "fieldLayout.createSequentialGroup()" + "\n" +
                "\t\t\t" + ".addGroup(fieldLayout.createParallelGroup()" + "\n"
        );
        for(String s: data.getFieldName()) {
            sb.append("\t\t\t\t" + ".addComponent(label" + s + ")" + "\n");
        }
        sb.append("\t\t\t" + ")" + "\n");

        sb.append("\t\t\t" + ".addGroup(fieldLayout.createParallelGroup()" + "\n");
        for(String s: data.getFieldName()) {
            sb.append("\t\t\t\t" + ".addComponent(" + s + ")" + "\n");
        }
        sb.append("\t\t\t" + ")" + "\n");
        sb.append("\t\t" + ");" + "\n");


        sb.append("\t\t" + "fieldLayout.setVerticalGroup(" + "\n" +
                "\t\t\t" + "fieldLayout.createSequentialGroup()" + "\n");

        for(String s: data.getFieldName()) {
            sb.append("\t\t\t" + ".addGroup(fieldLayout.createParallelGroup()" + "\n" +
                    "\t\t\t\t" + ".addComponent(label" + s + ")" + "\n" +
                    "\t\t\t\t" + ".addComponent(" + s + "))" + "\n"
            );
        }
        sb.append("\t\t" + ");" + "\n\n");

        sb.append("\t\t" + "topPanel.add(fieldPanel, BorderLayout.CENTER);" + "\n" +
                  "\t\t" + "JPanel buttonPanel = new JPanel(new FlowLayout());" + "\n\n"
        );

        for(int i = 0; i < data.getButtonName().length; i++) {
             sb.append("\t\t" + "JButton button" + data.getButtonName()[i] + " = new JButton(\"" + data.getButtonName()[i] + "\");" + "\n" +
                       "\t\t" + "button" + data.getButtonName()[i] + ".addActionListener(new " + data.getButtonValue()[i] + "(this) );" + "\n" +
                       "\t\t" + "buttonPanel.add(button" + data.getButtonName()[i] + ");" + "\n"
             );
        }
        sb.append("\n");

        sb.append("\t\t" + "topPanel.add(buttonPanel, BorderLayout.SOUTH);" + "\n" +
                  "\t\t" + "this.add(topPanel, BorderLayout.NORTH);" + "\n" +
                  "\n"   +
                  "\t\t" + "JPanel botPanel = new JPanel(new BorderLayout());" + "\n" +
                  "\t\t" + "JPanel statusPanel = new JPanel();" + "\n" +
                  "\t\t" + "JLabel statusLabel = new JLabel(\"STATUS\");" + "\n" +
                  "\t\t" + "statusPanel.add(statusLabel);" + "\n" +
                  "\t\t" + "botPanel.add(statusPanel, BorderLayout.NORTH);" + "\n" +
                  "\n"   +
                  "\t\t" + "JPanel boxPanel = new JPanel(new GridLayout(1,1));" + "\n" +
                  "\t\t" + "statusArea = new JTextArea();" + "\n" +
                  "\t\t" + "statusArea.setRows(12);" + "\n" +
                  "\t\t" + "JScrollPane scroll = new JScrollPane(statusArea);" + "\n" +
                  "\t\t" + "scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);" + "\n" +
                  "\t\t" + "scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);" + "\n" +
                  "\t\t" + "boxPanel.add(scroll);" + "\n" +
                  "\t\t" + "botPanel.add(boxPanel, BorderLayout.CENTER);" + "\n" +
                  "\n"   +
                  "\t\t" + "this.add(botPanel,BorderLayout.CENTER);" + "\n" +
                  "\n"   +
                  "\t"   + "}" + "\n\n"
        );

        sb.append("\t\t" + "public void appendToStatusArea(String str) {" + "\n" +
                  "\t\t" + "statusArea.append(str);" + "\n" +
                  "\t"   + "}" + "\n\n"
        );

        for(String s: data.getFieldName()) {
            sb.append("\t" + "public String getDC" + s + "() {" + "\n" +
                    "\t\t" + "return " + s + ".getText();" + "\n" +
                      "\t" + "}" + "\n\n" +
                      "\t" + "public void setDC" + s + "(String str) {" + "\n" +
                    "\t\t" + s + ".setText(str);" + "\n" +
                      "\t" + "}" + "\n\n"
            );
        }

        sb.append("\t" + "public static void main(String args[]) {" + "\n" +
                "\t\t" + "SwingUtilities.invokeLater(new Runnable() {" + "\n" +
                "\t\t\t" + "@Override" + "\n" +
                "\t\t\t" + "public void run() {" + "\n" +
                "\t\t\t\t" + settings.getFilename() +" myGui = new " + settings.getFilename() + "();" + "\n" +
                "\t\t\t\t" + "myGui.setVisible(true);" + "\n" +
                "\t\t\t" + "}" + "\n" +
                "\t\t" + "});" + "\n" +
                "\t" + "}" + "\n"
        );

        sb.append("}" + "\n\n");

        this.source = sb.toString();
    }

    /*
    This function takes a PM_Parser object as a parameter and uses the data contained within to generate
    java code to produce an interface for the earlier generated GUI.
    */
    public void generateFieldEdit(PM_Parser data) {
        StringBuilder sb = new StringBuilder();

        sb.append("interface " + settings.getFilename() + "FieldEdit {" + "\n\n");

        sb.append("\t" + "void appendToStatusArea(String str);" +"\n\n");

        for(String s: data.getFieldName()) {
            sb.append("\t" + "String getDC" + s + "();" + "\n\n" +
                      "\t" + "void setDC" + s + "(String str);" + "\n\n"
            );
        }

        sb.append("}" + "\n\n");

        this.fieldEdit = sb.toString();
    }

    public String getSource() {
        return source;
    }

    public String getFieldEdit() {
        return fieldEdit;
    }

}
