CC = gcc 
CFLAGS = -c -fPIC -g -pedantic -ansi
PLATFORM = $(shell uname)
JAVA_HOME = /usr/lib/jvm/java-6-sun

ifeq ($(PLATFORM) , Darwin)
	TARGETS = JNI_mac libpm_shared_mac
else
	TARGETS = JNI libpm_shared
endif

all: c_targets java_targets

c_targets: ParameterManager parsing $(TARGETS)

libpm_shared: ParameterManager parsing JNI
	$(CC) -shared -o c_src/libJNIpm.so c_src/ParameterManager.o c_src/parsing.o c_src/dialogc_PM_Parser.o

libpm_shared_mac: ParameterManager parsing JNI_mac
	$(CC) -shared -o c_src/libJNIpm.so c_src/ParameterManager.o c_src/parsing.o c_src/dialogc_PM_Parser.o

JNI:
	$(CC) $(CFLAGS) c_src/dialogc_PM_Parser.c -o c_src/dialogc_PM_Parser.o -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux

JNI_mac:
	$(CC) $(CFLAGS) c_src/dialogc_PM_Parser.c -o c_src/dialogc_PM_Parser.o -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/darwin

ParameterManager: 
	$(CC) $(CFLAGS) c_src/ParameterManager.c -o c_src/ParameterManager.o

parsing:
	$(CC) $(CFLAGS) c_src/parsing.c -o c_src/parsing.o

java_targets:
	javac dialogc/Dialogc.java dialogc/Generator.java dialogc/PM_Parser.java dialogc/Gui.java dialogc/Settings.java


clean:
	rm c_src/*.o
	rm c_src/*.so
	rm dialogc/*.class
