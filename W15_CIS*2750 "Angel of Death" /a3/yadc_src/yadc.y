/* YACC */
/* filename:   yadc.y
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*2750
 * assignment: 3
 *
 */


%{

    /* PREPROCESSOR STUFF */
    #define YYSTYPE char*
    #include <stdio.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include "generic_stack.h"


    /* FUNCTION DECLARATION */
    void yyerror(char *);
    char ** stackToArray(stack st, int count);
    int getIndex(char **target, char *term, int count);
    void cleanup();
    char * buildTitle(stack st);
    char * getFilename(char *filepath);
    void generateSource(char *configFilename, char *workingDir);


    /* VARIABLE DECLARATION */
    extern FILE *yyin;
    stack st;
    int i;

    int titleCount;
    char *title;

    int buttonCount;
    char **buttonNames;
    char **buttonValues;

    int fieldCount;
    char **fieldNames;
    char **fieldValues;

%}

%token TITLE FIELDS BUTTONS VALUE QUOTE
%token EQUALS SEMICOLON OPENBR CLOSEBR COMMA


%%

line:
    currentline SEMICOLON line
    | currentline
    | 
    ;

currentline:
    title
    | fields
    | buttons
    | value
    ;
    
title:
    TITLE EQUALS QUOTE VALUE QUOTE { title = $4; }
    | TITLE EQUALS QUOTE tlist QUOTE { title = buildTitle(st); }
    ;

tlist:
    VALUE tlist { stack_push(st,$1); titleCount++; } 
    | VALUE     { stack_push(st,$1); titleCount++; } 
    ;

fields:
    FIELDS EQUALS OPENBR flist CLOSEBR { fieldNames = stackToArray(st, fieldCount); fieldValues = malloc(sizeof(char *) * fieldCount); }
    | FIELDS EQUALS OPENBR CLOSEBR     { fieldNames = NULL; fieldValues = NULL; }
    ;

flist:
    QUOTE VALUE QUOTE COMMA flist   { stack_push(st, $2); fieldCount++; }
    | QUOTE VALUE QUOTE             { stack_push(st, $2); fieldCount++; }
    ;

buttons:
    BUTTONS EQUALS OPENBR blist CLOSEBR { buttonNames = stackToArray(st, fieldCount); buttonValues = malloc(sizeof(char *) * buttonCount); }
    | BUTTONS EQUALS OPENBR CLOSEBR     { buttonNames = NULL; buttonValues = NULL; }
    ;

blist:
    QUOTE VALUE QUOTE COMMA blist   { stack_push(st, $2); buttonCount++; }
    | QUOTE VALUE QUOTE             { stack_push(st, $2); buttonCount++; }
    ;

value:
    VALUE EQUALS QUOTE VALUE QUOTE  { 
                                        i = getIndex(fieldNames, $1, fieldCount); 
                                        if(i == -1) {

                                            i = getIndex(buttonNames, $1, buttonCount);
                                            if(i == -1) {
                                                printf("PARSE ERROR: no match found for %s\n", $1);

                                            } else {
                                                buttonValues[i] = $4;
                                            }

                                        } else {
                                            fieldValues[i] = $4;
                                        }
                                    }
    ;

%%

int main(int argc, char *argv[]) {
    if(argc >= 2) {
        yyin = fopen(argv[1],"r");
    }
    st = stack_init(); 
    buttonCount = 0; 
    fieldCount = 0; 
    titleCount = 0;

    yyparse();

    if(argc >= 3) {
        generateSource(argv[1], argv[2]);
    } else if(argc >= 2) {
        generateSource(argv[1], ".");
    } else {
        generateSource("NameNotSpecified.config",".");
    }
    
    #ifdef _DEBUG_
    printf("title = %s\n", title);

    for(i = 0; i < fieldCount; i++) {
        printf("%s = %s\n", fieldNames[i], fieldValues[i]);
    }

    for(i = 0; i < buttonCount; i++) {
        printf("%s = %s\n", buttonNames[i], buttonValues[i]);
    }
    #endif

    if(argc >= 2) {
        fclose(yyin);
    }

    cleanup();
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

/*
Pop all items from "st" into a new char** and return it.
*/
char ** stackToArray(stack st, int count) {
    char **newArr;
    int i;

    newArr = malloc(sizeof(char *) * count);
    for(i = 0; i < count; i++) {
        newArr[i] = (char *)stack_pop(st);
    }

    return newArr;
}

/* 
This function locates the passed "term" in "target" char* array,
either returning the index of "term" in "target" or -1 if "term"
does not exist in "target".
*/
int getIndex(char **target, char *term, int count) {
    int i;
    if(target == NULL || term == NULL) {
        return -1;
    }

    for(i = 0; i < count; i++) {
        if(strcmp(target[i],term) == 0) {
            return i;
        }
    }

    return -1;
}

/* 
This function frees all memory allocated to stored parsed data.
*/
void cleanup() {

    free(st);

    if(fieldNames != NULL) {
        for(i = 0; i < fieldCount; i++) {
            free(fieldNames[i]);
            free(fieldValues[i]);
        }

        free(fieldNames);
        free(fieldValues);
    }
    
    if(buttonNames != NULL) {
        for(i = 0; i < buttonCount; i++) {
            free(buttonNames[i]);
            free(buttonValues[i]);
        }

        free(buttonNames);
        free(buttonValues);
    }
}

char * buildTitle(stack st) {
    char *outStr;
    char *temp;

    outStr = malloc(sizeof(char) * 3);

    for(i = 0; i < titleCount; i++) {
        temp = (char*)stack_pop(st);

        outStr = realloc(outStr, sizeof(char) * (strlen(outStr) + strlen(temp) + 2));

        if(i != 0) {
            strcat(outStr," ");
            strcat(outStr, temp);
        } else {
            strcpy(outStr, temp);
        }
        free(temp);
    }
    
    return outStr;
}

/*
This function takes the full path to a file as a parameter and returns 
just the file name.  
IN:  folder/folder/sample.extension
OUT: sampleo
*/
char * getFilename(char *filepath) {
    int start = 0, end;
    int length;
    int i, k;
    char * name;

    length = strlen(filepath);

    for(i = length; i > -1; i--) {
        if(filepath[i] == '.') {
            end = i;
            break;
        }
    }

    for(i = length; i > -1; i--) {
        if(filepath[i] == '/' || filepath[i] == '\\') {
            start = i + 1;
            break;
        }
    }

    name = malloc(sizeof(char) * (end - start + 1));
    k = 0;

    for(i = start; i < end; i++) {
        name[k] = filepath[i];
        k++;
    }

    return name;
}

/*
This function generates 3 Java files:
1. Java GUI/Main file
2. Java Interface file
3. IllegalFieldValueException.java
*/
void generateSource(char *configFilename, char *workingDir) {
    int i;
    int length, pathLen;
    int validDir;
    char *directoryPath;
    char *projectName;
    char *javaSRC;
    char *javaInterface;
    char *javaException;
    char *command;
    FILE *fp;

    if(workingDir == NULL || strcmp(workingDir,".") == 0) {
        validDir = 0;
    } else {
        validDir = 1;
    }

    projectName = getFilename(configFilename);

    length = strlen(projectName);
    pathLen = length + 1;
    if(validDir) {
        pathLen += strlen(workingDir) + 1;
    }

    directoryPath = malloc(sizeof(char) * (pathLen + 1));
    if(validDir) {
        strcpy(directoryPath,workingDir);
        strcat(directoryPath,"/");
        strcat(directoryPath,projectName);
    } else {
        strcpy(directoryPath,projectName);
    }
    strcat(directoryPath,"/");

    pathLen = strlen(directoryPath);

    command = malloc(sizeof(char) *(10 + pathLen));
    strcpy(command, "mkdir -p ");
    strcat(command, directoryPath);

    system(command);

    javaSRC = malloc(sizeof(char) * (length + pathLen + 6));
    strcpy(javaSRC,directoryPath);
    strcat(javaSRC,projectName);
    strcat(javaSRC,".java");

    javaInterface = malloc(sizeof(char) * (length + pathLen+ 15));
    strcpy(javaInterface,directoryPath);
    strcat(javaInterface, projectName);
    strcat(javaInterface, "FieldEdit.java");

    javaException = malloc(sizeof(char) * (pathLen + 32));
    strcpy(javaException,directoryPath);
    strcat(javaException, "IllegalFieldValueException.java");

    fp = fopen(javaException, "w");

    fprintf(fp,
        "public class IllegalFieldValueException extends Exception {" "\n"
        "\t" "public IllegalFieldValueException(String message) {" "\n"
        "\t\t" "super(message);" "\n"
        "\t" "}" "\n"
        "\t" "public IllegalFieldValueException(String message, Throwable throwable) {" "\n"
        "\t\t" "super(message, throwable);" "\n"
        "\t" "}" "\n"
        "}" "\n"
        "\n"
    );
    fclose(fp);

    /* Generate Java GUI Source Code */
    fp = fopen(javaSRC, "w");

    fprintf(fp, 
        "import javax.swing.*;" "\n"
        "import java.awt.*;" "\n"
        "import java.util.regex.Pattern;" "\n"
        "\n"
        "public class %s extends JFrame implements %sFieldEdit {" "\n"
        ,projectName,projectName
    );

    for(i = 0; i < fieldCount; i++) {
        fprintf(fp, "\t" "private JTextField %s;" "\n", fieldNames[i]);
    }

    fprintf(fp, "\t" "private JTextArea statusArea;" "\n\n");
    fprintf(fp, 
        "\t"   "public %s () {" "\n" 
        "\t\t" "super(\"%s\");" "\n"
        "\t\t" "setDefaultCloseOperation(EXIT_ON_CLOSE);" "\n"
        "\t\t" "setLayout(new BorderLayout());" "\n"
        "\t\t" "setSize(350,600);" "\n"
        "\t\t" "init();" "\n"
        "\t\t" "pack();" "\n"
        "\t\t" "}" "\n\n"
        ,projectName,title
    );
    fprintf(fp,
        "\t"   "private void init() {\n"
        "\t\t" "JPanel topPanel = new JPanel(new BorderLayout());\n"
        "\t\t" "\n"
        "\t\t" "JPanel fieldPanel = new JPanel();\n"
        "\t\t" "GroupLayout fieldLayout = new GroupLayout(fieldPanel);\n"
        "\t\t" "fieldPanel.setLayout(fieldLayout);\n"
        "\t\t" "fieldLayout.setAutoCreateGaps(true);\n"
        "\t\t" "fieldLayout.setAutoCreateContainerGaps(true);\n"
        "\n"
    );

    for(i = 0; i < fieldCount; i++) {
        fprintf(fp,
            "\t\t" "%s= new JTextField(15);" "\n"
            "\t\t" "JLabel label%s = new JLabel(\"%s\");" "\n"
            ,fieldNames[i] ,fieldNames[i], fieldNames[i]
        );
    }
    fprintf(fp,"\n");

    fprintf(fp,
        "\t\t"   "fieldLayout.setHorizontalGroup(" "\n"
        "\t\t\t" "fieldLayout.createSequentialGroup()" "\n"
        "\t\t\t" ".addGroup(fieldLayout.createParallelGroup()" "\n"
    );

    for(i = 0; i < fieldCount; i++) {
        fprintf(fp, "\t\t\t\t" ".addComponent(label%s)" "\n", fieldNames[i]);
    }
    fprintf(fp,"\t\t\t" ")" "\n");

    fprintf(fp,"\t\t\t" ".addGroup(fieldLayout.createParallelGroup()" "\n");
    for(i = 0; i < fieldCount; i++) {
        fprintf(fp,"\t\t\t\t" ".addComponent(%s)" "\n", fieldNames[i]);
    }
    fprintf(fp,"\t\t\t" ")" "\n");
    fprintf(fp,"\t\t"   ");" "\n");


    fprintf(fp,
        "\t\t"   "fieldLayout.setVerticalGroup(" "\n"
        "\t\t\t" "fieldLayout.createSequentialGroup()" "\n"
    );
    for(i = 0; i < fieldCount; i++) {
        fprintf(fp,
            "\t\t\t"   ".addGroup(fieldLayout.createParallelGroup()" "\n"
            "\t\t\t\t" ".addComponent(label%s)" "\n"
            "\t\t\t\t" ".addComponent(%s))" "\n"
            ,fieldNames[i],fieldNames[i]
        );
    }
    fprintf(fp, "\t\t" ");" "\n\n");

    fprintf(fp, 
        "\t\t" "topPanel.add(fieldPanel, BorderLayout.CENTER);" "\n"
        "\t\t" "JPanel buttonPanel = new JPanel(new FlowLayout());" "\n\n"
    );

    /* Generate Buttons */
    for(i = 0; i < buttonCount; i++) {
        fprintf(fp,
            "\t\t" "JButton button%s = new JButton(\"%s\");" "\n"
            "\t\t" "button%s.addActionListener(new %s(this) );" "\n"
            "\t\t" "buttonPanel.add(button%s);" "\n"
            ,buttonNames[i],buttonNames[i],buttonNames[i],buttonValues[i],buttonNames[i]
        );
    }
    fprintf(fp,"\n");

    fprintf(fp,
        "\t\t" "topPanel.add(buttonPanel, BorderLayout.SOUTH);" "\n"
        "\t\t" "this.add(topPanel, BorderLayout.NORTH);" "\n"
        "\n"  
        "\t\t" "JPanel botPanel = new JPanel(new BorderLayout());" "\n"
        "\t\t" "JPanel statusPanel = new JPanel();" "\n"
        "\t\t" "JLabel statusLabel = new JLabel(\"STATUS\");" "\n"
        "\t\t" "statusPanel.add(statusLabel);" "\n"
        "\t\t" "botPanel.add(statusPanel, BorderLayout.NORTH);" "\n"
        "\n"  
        "\t\t" "JPanel boxPanel = new JPanel(new GridLayout(1,1));" "\n"
        "\t\t" "statusArea = new JTextArea();" "\n"
        "\t\t" "statusArea.setRows(12);" "\n"
        "\t\t" "JScrollPane scroll = new JScrollPane(statusArea);" "\n"
        "\t\t" "scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);" "\n"
        "\t\t" "scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);" "\n"
        "\t\t" "boxPanel.add(scroll);" "\n"
        "\t\t" "botPanel.add(boxPanel, BorderLayout.CENTER);" "\n"
        "\n"  
        "\t\t" "this.add(botPanel,BorderLayout.CENTER);" "\n"
        "\n"  
        "\t"   "}" "\n\n"
    );

    fprintf(fp,
        "\t" "public void appendToStatusArea(String str) {" "\n"
        "\t\t" "statusArea.append(str);" "\n"
        "\t" "}" "\n"
        "\n"
        "\t" "private boolean integerCheck(String str) {" "\n"
        "\t\t" "if(Pattern.matches(\"[0-9]+\",str)) {" "\n"
        "\t\t\t" "return true;" "\n"
        "\t\t" "}" "\n"
        "\t\t" "return false;" "\n"
        "\t" "}" "\n"
        "\n"
        "\t" "private boolean floatCheck(String str) {" "\n"
        "\t\t" "if(Pattern.matches(\"[0-9][0-9.]+\",str)) {" "\n"
        "\t\t\t" "return true;" "\n"
        "\t\t" "}" "\n"
        "\t\t" "return false;" "\n"
        "\t}" "\n"
        "\n"
    );

    for(i = 0; i < fieldCount; i++) {
        if(strcmp(fieldValues[i], "string") == 0) {
            fprintf(fp,
                "\t" "public String getDC%s() throws IllegalFieldValueException {" "\n"
                "\t\t" "return %s.getText();" "\n"
                "\t" "}" "\n\n"
                ,fieldNames[i],fieldNames[i]
            );
        } else {
            fprintf(fp,
                "\t" "public String getDC%s() throws IllegalFieldValueException {" "\n"
                "\t\t" "if(%sCheck(%s.getText())) {" "\n"
                "\t\t\t" "return %s.getText();" "\n"
                "\t\t" "} else {" "\n"
                "\t\t\t" "throw new IllegalFieldValueException(%s.getText());" "\n"
                "\t\t" "}" "\n"
                "\t" "}" "\n\n"
                ,fieldNames[i],fieldValues[i],fieldNames[i],fieldNames[i],fieldNames[i]
            );
        }
        
        fprintf(fp,
            "\t" "public void setDC%s(String str) {" "\n"
            "\t\t" "%s.setText(str);" "\n"
            "\t" "}" "\n\n"
            ,fieldNames[i],fieldNames[i]
        );
    }

    fprintf(fp,
        "\t" "public static void main(String args[]) {" "\n"
        "\t\t" "SwingUtilities.invokeLater(new Runnable() {" "\n"
        "\t\t\t" "@Override" "\n"
        "\t\t\t" "public void run() {" "\n"
        "\t\t\t\t" "%s myGui = new %s();" "\n"
        "\t\t\t\t" "myGui.setVisible(true);" "\n"
        "\t\t\t" "}" "\n"
        "\t\t" "});" "\n"
        "\t" "}" "\n"
        ,projectName,projectName
    );
    fprintf(fp,"}" "\n\n");

    fclose(fp); 


    /* Generate Interface */
    fp = fopen(javaInterface, "w");

    fprintf(fp,"interface %sFieldEdit {" "\n\n", projectName);

    fprintf(fp,"\t" "void appendToStatusArea(String str);" "\n\n");

    for(i = 0; i < fieldCount; i++) {
        fprintf(fp,
            "\t" "String getDC%s() throws IllegalFieldValueException;" "\n\n"
            "\t" "void setDC%s(String str);" "\n\n"
            ,fieldNames[i],fieldNames[i]
        );
    }

    fprintf(fp,"}" "\n\n");

    fclose(fp);

    free(directoryPath);
    free(projectName);
    free(javaSRC);
    free(javaInterface);
    free(javaException);
    free(command);
}

