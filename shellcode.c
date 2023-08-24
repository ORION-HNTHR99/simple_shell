#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * cleanup - Frees allocated memory.
 * @input_buffer: The buffer to be cleaned up.
 */
void cleanup(char *input_buffer)
{
	free(input_buffer);
}

/**
 * execute_command - Executes the given command using execve.
 * @command: The command to execute.
 */
void execute_command(const char *command)
{
	char **args = NULL;
	int arg_count = 2;

	args = (char **)malloc(arg_count * sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	args[0] = strdup(command);
	if (args[0] == NULL)
	{
		perror("strdup");
		free(args);
		exit(EXIT_FAILURE);
	}

	args[1] = NULL;

	if (execve(command, args, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}

	free(args[0]);
	free(args);
}

/**
 * main_loop - Main loop for shell execution.
 */
void main_loop(void)
{
	char *input_buffer;
	size_t bufsize = BUFFER_SIZE;
	pid_t child_pid;

	while (1)
	{
		input_buffer = (char *)malloc(bufsize * sizeof(char));
		if (input_buffer == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		printf("myshell$ ");
		getline(&input_buffer, &bufsize, stdin);
		input_buffer[strcspn(input_buffer, "\n")] = '\0';

		if (strcmp(input_buffer, "exit") == 0)
		{
			cleanup(input_buffer);
			exit(EXIT_SUCCESS);
		}

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			cleanup(input_buffer);
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
			execute_command(input_buffer); /* Child process */
		else
		{
			wait(NULL); /* Parent process */
			cleanup(input_buffer);
		}
	}
}

/**
 * main - Entry point for the simple shell program.
 * Return: Always 0.
 */
int main(void)
{
	main_loop();
	return (0);
}
