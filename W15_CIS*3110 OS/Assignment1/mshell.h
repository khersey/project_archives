/* filename:   mshell.h
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 1
 *
 * Basic Linux Shell written in C.  Contains functionality allowing
 * for input and output redirection as well as multiple pipes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int runCommand(char **args, int background, int input, int output, int pipes, char *in_filename, char *out_filename);

void arg(char **args);

void add(char **args);

char **nextCommand(char **args);

int countPipes(char **args);

int inBackground(char **args);

int checkOutput(char **args, char **filename);

int checkInput(char **args, char **filename);

