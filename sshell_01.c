#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

/**
 * execute_command - Executes a command in the shell.
 * @command: The command to execute.
 */
void execute_command(const char *command)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		execlp(command, command, NULL);
		perror("exec error");
		exit(EXIT_FAILURE);
	}
	else if (child_pid < 0)
	{
		perror("fork error");
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
