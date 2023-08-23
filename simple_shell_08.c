#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 1024

/* Function prototypes */
char *custom_getline(void);
char **split_input(char *input);
void handle_exit(char **args);

int main(void)
{
	char *input;
	char **args;
	int i;

	while (1)
	{
		input = custom_getline();
		if (!input)
		{
			printf("End of input\n");
			break;
		}

		args = split_input(input);
		if (args)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				handle_exit(args);
			}
			else
			{
				i = 0;
				while (args[i] != NULL)
				{
					printf("Arg[%d]: %s\n", i, args[i]);
					free(args[i]);
					i++;
				}
				free(args);
			}
		}

		free(input);
	}

	return (0);
}

char *custom_getline(void)
{
	ssize_t bufsize = 0;
	char *buffer = NULL;

	if (getline(&buffer, (size_t *)&bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(buffer);
			return (NULL);
		}
		perror("getline");
		exit(EXIT_FAILURE);
	}

	return (buffer);
}

char **split_input(char *input)
{
	char **args = NULL;
	char *arg = strtok(input, " \t\n");

	if (!arg)
		return (NULL);

	int arg_count = 0;
	while (arg)
	{
		args = realloc(args, sizeof(char *) * (arg_count + 1));
		if (!args)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}

		args[arg_count] = strdup(arg);
		if (!args[arg_count])
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}

		arg_count++;
		arg = strtok(NULL, " \t\n");
	}
	args = realloc(args, sizeof(char *) * (arg_count + 1));
	if (!args)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	args[arg_count] = NULL;

	return (args);
}

void handle_exit(char **args)
{
	if (args[1])
	{
		int exit_status = atoi(args[1]);
		free(args[0]);
		free(args);
		exit(exit_status);
	}
	else
	{
		free(args[0]);
		free(args);
		exit(0);
	}
}
