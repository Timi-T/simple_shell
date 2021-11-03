#include "shell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/**
 * execute_command - function1 to execute a the commands
 *
 * @arg: file path of command
 * @command: a linked list containing the command and arguments
 * @input: in put string from user
 *
 * Return: nothing
 */

void execute_command(char *arg, dir_list *command, char *input)
{
	char *com;
	int id, i = 0;
	char **array;
	dir_list *command_copy = command;

	com = command->dir;
	array = malloc(strlen(input));
	while (command_copy != NULL)
	{
		array[i] = malloc(strlen(command_copy->dir) + 1);
		array[i] = command_copy->dir;
		command_copy = command_copy->next;
		i++;
	}
	array[i] = NULL;
	if (*arg != 'x' && *(arg + 1) != '\0')
	{
		id = fork();
		if (id != 0)
			wait(0);
		else
		{
			if (*com == '/')
			{
				if (execve(com, array, NULL) == -1)
				{
					perror("./shell");
					kill(getpid(), SIGKILL);
				}
			}
			else if (execve(arg, array, NULL) == -1)
			{
				perror("./shell");
				kill(getpid(), SIGKILL);
			}
		}
	}
	else
		perror("./shell");
	free(array);
}

/**
 * check_env - function2 to check if the input is env
 *
 * @input: input from user
 * @environment: array of environment variables
 *
 * Return: 1 if input is env otherwise 0
 */

int check_env(char *input, char **environment)
{
	char **environment1 = environment;
	int diff = 0;
	char *in = input;
	char *env_code = "env";

	if (*input == '\0')
		return (0);
	while (*in != '\0')
	{
		if (*in != *env_code)
		{
			diff++;
		}
		in++;
		env_code++;
	}
	if (diff == 0)
	{
		while (*environment1 != NULL)
		{
			printf("%s\n", *environment1);
			environment1++;
		}
		return (1);
	}
	return (0);
}
