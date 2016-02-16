CC = gcc 
CFLAGS = -c -fPIC -g -pedantic -ansi
PLATFORM = $(shell uname)
RELEASE = $(shell awk -F= '/^NAME/{print $2}' /etc/os-release)


ifeq ($(PLATFORM) , Darwin)
	JNI = JNI_mac
else
	ifeq ($(RELEASE), NAME="Ubuntu")
		JNI = JNI_ubuntu
	else
		JNI = JNI_lab
	endif
endif


all: libpm dialogc yadc

libpm: ParameterManager parsing $(JNI)
	$(CC) -shared -o c_src/libJNIpm.so c_src/ParameterManager.o c_src/parsing.o c_src/dialogc_PM_Parser.o

JNI_ubuntu:
	$(CC) $(CFLAGS) c_src/dialogc_PM_Parser.c -o c_src/dialogc_PM_Parser.o -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux

JNI_mac:
	$(CC) $(CFLAGS) c_src/dialogc_PM_Parser.c -o c_src/dialogc_PM_Parser.o -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/darwin

JNI_lab:
	$(CC) $(CFLAGS) c_src/dialogc_PM_Parser.c -o c_src/dialogc_PM_Parser.o -I /usr/lib/jvm/java-6-sun/include -I /usr/lib/jvm/java-6-sun/include/linux

ParameterManager: 
	$(CC) $(CFLAGS) c_src/ParameterManager.c -o c_src/ParameterManager.o

parsing:
	$(CC) $(CFLAGS) c_src/parsing.c -o c_src/parsing.o

dialogc:
	javac dialogc/Dialogc.java dialogc/Generator.java dialogc/PM_Parser.java dialogc/Gui.java dialogc/Settings.java

yadc: yacc lex
	$(CC) yadc_src/lex.yy.c yadc_src/y.tab.c yadc_src/generic_stack.c -o yadc_src/yadc

lex:
	lex yadc_src/yadc.l
	mv lex.yy.c yadc_src/

yacc:
	yacc -d yadc_src/yadc.y 
	mv y.tab.c yadc_src/
	mv y.tab.h yadc_src/

clean:
	rm c_src/*.o
	rm c_src/*.so
	rm dialogc/*.class
	rm yadc_src/y.*
	rm yadc_src/lex.yy.c
	rm yadc_src/yadc
