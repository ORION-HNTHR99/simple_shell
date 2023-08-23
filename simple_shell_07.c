#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 1024

/* Function prototypes */
char *custom_getline(void);
char **split_input(char *input);

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
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
			i = 0;
			while (args[i] != NULL)
			{
				printf("Arg[%d]: %s\n", i, args[i]);
				free(args[i]);
				i++;
			}
			free(args);
		}

		free(input);
	}

	return (0);
}

/**
 * custom_getline - Read input from the user using a custom
 * implementation of getline.
 *
 * Return: A dynamically allocated string containing the user's input,
 *         or NULL if no more input is available.
 */
char *custom_getline(void)
{
	ssize_t bufsize = 0;
	char *buffer = NULL;

	if (getline(&buffer, (size_t *)&bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(buffer);
			return (NULL); /* End of input */
		}
		perror("getline");
		exit(EXIT_FAILURE);
	}

	return (buffer);
}

/**
 * split_input - Split the input string into arguments.
 *
 * @input: The input string.
 * Return: An array of pointers to arguments, or NULL on failure.
 */
char **split_input(char *input)
{
	char **args = NULL;
	char *arg = strtok(input, " \t\n");
	int arg_count = 0;

	if (!arg)
		return (NULL);

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
