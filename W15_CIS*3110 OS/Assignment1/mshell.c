/* filename:   mshell.c
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 1
 *
 * Basic Linux Shell written in C.  Contains functionality allowing
 * for input and output redirection as well as multiple pipes.
 */

#include "mshell.h"

/*

This function takes a line from the terminal and parses it into individual arguements
by leveraging the Flex parser tool.

*/
extern char **getln();


int main() {
	int background, input, output, pipes;
	char **args;
	char *in_filename;
	char *out_filename; 
	
	while(1) {
		printf(">");
		args = getln();

		if(args[0] == NULL) { /* empty line was entered */
			continue;
		} else if((strcmp(args[0],"exit")) == 0) {
			exit(0);
		} else if((strcmp(args[0],"arg")) == 0) {
			arg(args);
			continue;
		} else if((strcmp(args[0],"add")) == 0) {
			add(args);
			continue;
		}

		input = checkInput(args, &in_filename);
		if(input == -1) {
			printf("ERROR: Syntax error occured relating to input redirection\n");
			continue;
		}

		output = checkOutput(args, &out_filename);
		if(output == -1) {
			printf("ERROR: Syntax error occured relating to output redirection\n");
			continue;
		}

		pipes = countPipes(args);
		background = inBackground(args);

		runCommand(args, background, input, output, pipes, in_filename, out_filename);

	}

	return 0;
}

/*

This function is responsible for running the commands the user inputs.  This includes
piping, input redirection and output redirection. If a background parameter of 1 is
passed in, then the process will be executed in the background.

*/
int runCommand(char **args, int background, int input, int output, int pipes, char *in_filename, char *out_filename) {
	pid_t child;
	int status, i, p;
	int fd[2*pipes];
	char **commands;

	if(pipes == 0) { /* No pipes */
		child = fork();

		if(child == EAGAIN || child == ENOMEM) {
			perror("ERROR FORKING: ");
			return -1;
		}

		if(child == 0) {
			if (input) {
				freopen(in_filename, "r", stdin);
			}

			if(output) {
				freopen(out_filename, "w+", stdout);
			}

			execvp(args[0], args);

			exit(-1);
		}
		if(background) {
			waitpid(child, &status, 0);
		}

		for(i=0; args[i] != NULL; i++) {
			free(args[i]);
			args[i] = NULL;
		}

	} else {       /* pipes */

		for(i = 0; i < pipes; i++) {
			if(pipe(fd + i*2) < 0) {
				return 0;
			}
		}
		commands = nextCommand(args);
		
		p = 0;
		while(commands != NULL) {
			child = fork();

			if(child == 0) {

				if(p < pipes) {            /* dont run for last command */
					dup2(fd[2*p+1], 1);   /* pipe output */
				} else if (output) {
					freopen(out_filename, "w+", stdout);
				}

				if(p != 0) {               /* dont run for first command*/
					dup2(fd[(p-1)*2], 0); /* pipe input */
				} else if(input) {
					freopen(in_filename, "r", stdin);
				}

				for(i = 0; i < 2*pipes; i++) {
					close(fd[i]);
				}

				execvp(commands[0], commands);

				exit(-1);
			}

			for(i=0; commands[i] != NULL; i++) {
				free(commands[i]);
				commands[i] = NULL;
			}

			commands = nextCommand(args);
			p++;
		}

		for(i = 0; i < 2*pipes; i++) {
			close(fd[i]);
		}

		if(background) {
			for(i = 0; i <= pipes; i++) {
				waitpid(child, &status, 0);
			}
		}
		

	}

	return 1;
}


/*

This function counts the amount of arguments entered, and prints it.

*/
void arg(char **args) {
	int i;

	for(i = 0; args[i] != NULL; i++);

	printf("argc = %i, args = ",i-1);

	for(i = 1; args[i] != NULL; i++) {
		if(i != 1) {
			printf(",");
		}
		printf("%s", args[i]);
	}

	printf("\n");

}

/*

This function add up the numeric value of all arguments and prints it.

*/
void add(char **args) {
	long int sum, current;
	short i;

	sum = 0;

	for (i = 1; args[i] != NULL; ++i)
	{
		if(i != 1) {
			printf(" + ");
		}
		current = strtol(args[i],NULL,0);
		printf("%s",args[i]);
		sum += current;
	}

	printf(" = %li\n", sum);

}

/*

This function takes all arguments in front of the first | in args and returns
it as a new character pointer array.  All arguments up to and including the |
are removed from args.  If args is already empty, this function returns NULL.

*/
char **nextCommand(char **args) {
	char **commands;
	int i, j;

	if(args[0] == NULL) {
		return NULL;
	}

	for(i = 0; args[i] != NULL; i++ ) {
		if(strcmp(args[i],"|") == 0) {
			break; 
		}
	}

	if(args[i] == NULL) { /* last command */
		commands = malloc(sizeof(char*) * (i + 1));
		for(j = 0; j < i; j++) {
			commands[j] = args[j];
			args[j] = NULL;
		}
		commands[i] = NULL;

	} else {
		commands = malloc(sizeof(char*) * (i + 1));
		for(j = 0; j < i; j++) {
			commands[j] = args[j];
		}
		free(args[i]);
		args[i] = NULL;
		commands[i] = NULL;
		i++;
		for(j = 0; args[i] != NULL; j++) {
			args[j] = args[i];
			i++;
		}
		for(;args[j] != NULL;j++) {
			args[j] = NULL;
		}

	}

	return commands;
}

/*

Counts the amount of pipes "|" present in args and returns it.

*/
int countPipes(char **args) {
	int i, count;
	count = 0;

	for(i=0; args[i] != NULL; i++) {
		if((strcmp("|",args[i])) == 0) {
			count++;
		}
	}

	return count;
}

/*

Returns 0 if the last element of args is "&", returns 1 otherwise.

*/
int inBackground(char **args) {
	int i;

	for(i = 1; args[i] != NULL; i++);

	if((strcmp(args[i-1],"&")) == 0) {
		free(args[i-1]);
		args[i-1] = NULL;
		return 0;
	}

	return 1;
}

/*

Looks through args to see if an element exists which is ">", and if true will
remove this element from args.  It will then point **filename to the following element
before moving every element up by 2 positions.  Returns 1 if ">" is found, -1 if 
it is found but there is no following element, and 0 if it is not found.

*/
int checkOutput(char **args, char **filename) {
	int i;
	*filename = NULL;

	for(i=0; args[i] != NULL; i++) {
		if((strcmp(args[i],">")) == 0) {
			if(args[i+1] != NULL) {
				*filename = args[i+1];
			} else {
				return -1;
			}
			free(args[i]);
			break;
		}
	}
	if(*filename != NULL) {
		for(; args[i-1] != NULL; i++ ) {
			args[i] = args[i+2];
		}
		return 1;
	}
	return 0;
}

/*

Looks through args to see if an element exists which is "<", and if true will
remove this element from args.  It will then point **filename to the following element
before moving every element up by 2 positions.  Returns 1 if "<" is found, -1 if 
it is found but there is no following element, and 0 if it is not found.

*/
int checkInput(char **args, char **filename) {
	int i;
	*filename = NULL;

	for(i=0; args[i] != NULL; i++) {
		if((strcmp(args[i],"<")) == 0) {
			if(args[i+1] != NULL) {
				*filename = args[i+1];
			} else {
				return -1;
			}
			free(args[i]);
			break;
		}
	}
	if(*filename != NULL) {
		for(; args[i-1] != NULL; i++ ) {
			args[i] = args[i+2];
		}
		return 1;
	}
	return 0;
}


