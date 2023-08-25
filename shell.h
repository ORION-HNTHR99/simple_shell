#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT_SIZE 100

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void);

/**
 * execute_command - Executes a command in the shell.
 * @command: The command to execute.
 */
void execute_command(const char *command);

#endif
