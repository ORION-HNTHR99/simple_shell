#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 1024

/* Function prototypes */
char *custom_getline(void);

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input;

	while (1)
	{
		input = custom_getline();
		if (!input)
		{
			printf("End of input\n");
			break;
		}
		printf("You entered: %s\n", input);
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
	static char buffer[MAX_INPUT_LENGTH];
	static size_t buffer_pos;
	static size_t buffer_size;

	char c;
	char *line = NULL;
	size_t line_pos = 0;

	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			ssize_t bytes_read = read(STDIN_FILENO, buffer, MAX_INPUT_LENGTH);

			if (bytes_read <= 0)
			{
				if (line && line[0] != '\0')
				{
					return (line);
				}
				free(line);
				return (NULL);
			}
			buffer_pos = 0;
			buffer_size = (size_t) bytes_read;
		}

		c = buffer[buffer_pos++];
		if (c == '\n' || c == '\0')
		{
			if (!line)
			{
				line = malloc(line_pos + 1);
				if (!line)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}
			}
			line[line_pos] = '\0';
			return (line);
		}

		if (!line)
		{
			line = malloc(MAX_INPUT_LENGTH);
			if (!line)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
		}
		line[line_pos++] = c;
	}
}
