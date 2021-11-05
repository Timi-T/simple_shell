#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: array of arguments
 * @env: array of environment variables
 *
 * Return: nothing
 */

int main(int ac, char **av, char **env)
{
	char *input, *arg;
	size_t len = 0;
	int exit_switch, env_code, end_of_file;
	dir_list *args_link;
	char **environment1 = env;

	input = NULL;
	if (ac > 1)
	{
		write(2, "Usage: ", 7);
		write(2, av[0], strlen(av[0]));
		printf("\n");
		exit(0);
	}
	while (1)
	{
		if ((end_of_file = getline(&input, &len, stdin)) != EOF)
		{
			input[strlen(input) - 1] = '\0';
			env_code = check_env(input, environment1);
			if (*input != '\0' && env_code == 0)
			{
				exit_switch = exit_code(input);
				if (exit_switch == 0)
					break;
				args_link = get_arg_link(input);
				arg = get_dir(args_link, environment1);
				execute_command(arg, args_link, input);
			}
			else
				continue;
		}
		else
			break;
	}
	free(input);
	return (0);
}
