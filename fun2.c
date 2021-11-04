#include <stdio.h>
#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * print_list - function1 to print a linked list
 *
 * @head: pointer to first node of list
 *
 * Return: nothing
 */

void print_list(dir_list *head)
{
	dir_list *h = head;

	while (h != NULL)
	{
		printf("%s\n", h->dir);
		h = h->next;
	}
}

/**
 * join - function2 to join two strings
 *
 * @dir: string 1
 * @com: string 2
 *
 * Return: the joined string
 */

char *join(char *dir, char *com)
{
	char *s;
	int i = 0;
	size_t j = 0;

	s = malloc(strlen(dir) + strlen(com) + 1);
	while (j != (strlen(dir)))
	{
		s[j] = dir[j];
		j++;
	}
	while (j != (strlen(dir) + strlen(com)))
	{
		s[j] = com[i];
		j++;
		i++;
		s[j] = '\0';
	}
	return (s);
	free(s);
}

/**
 * fix_string - function3 to fix a string
 *
 * @str: string to be fixed
 *
 * Return: fixed string
 */

char *fix_string(char *str)
{
	int i = 0;
	int j;
	char *s;

	j = strlen(str);
	s = malloc(j);
	while (str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
	free(s);
}

/**
 * get_arg_link - function4 to get the linked list containing input strings
 *
 * @input: input to get strings from
 *
 * Return: a pointer to the first node of the list
 */

dir_list *get_arg_link(char *input)
{
	char *arg, *in;
	int strings, str = 1;
	dir_list *head, *h;

	in = input;
	strings = get_strings(input);
	arg = strtok(in, " ");
	head = malloc(strlen(arg) + sizeof(dir_list));
	head->dir = fix_string(arg);
	head->next = NULL;
	h = head;
	while (str < strings)
	{
		arg = strtok(NULL, " ");
		arg = fix_string(arg);
		h = add_node(head, arg);
		str++;
	}
	return (h);
	free(head);
}

/**
 * get_dir - function5 to get directory from path
 *
 * @argument: a linked list containing the command and arguments
 * @environment: array of environment variables
 *
 * Return: the directory containing the executable file with command name
 */

char *get_dir(dir_list *argument, char **environment)
{
	dir_list *path, *p, *arg = argument;
	char *p_c, *pdir;
	struct stat st;
	char **environment1 = environment;

	path = path_dir(environment1);
	p = path;
	while (p != NULL && *(arg->dir) != '/')
	{
		pdir = join(p->dir, "/");
		p_c = join(pdir, arg->dir);
		if (stat(p_c, &st) == 0)
		{
			return (p_c);
		}
		p = p->next;
	}
	if (*(arg->dir) == '/')
	{
		return ("/");
	}
	return ("x");
}
