#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * get_strings - function1 to get the number of words in a string.
 *
 * @str: string to get words from
 *
 * Return: number of strings
 */

int get_strings(char *str)
{
	int strings = 1;

	if (*str == '\0')
	{
		return (0);
	}
	while (*str != '\0')
	{
		if (*str == 32 && (*(str + 1) != 32 && *(str + 1) != '\0'))
		{
			strings++;
		}
		str++;
	}
	return (strings);
}

/**
 * exit_code - function2 to check command to break while loop
 *
 * @i: command being checked
 *
 * Return: 0 if the command is an exit code
 */

int exit_code(char *i)
{
	int diff = 0;
	char *code = "exit";

	while (*i != '\0')
	{
		if (*i != *code)
		{
			diff++;
		}
		code++;
		i++;
	}
	return (diff);
}

/**
 * _getenv - function3  to get an environment variable
 *
 * @name: name of the environment variable to check for
 * @environment: array of environment variables
 *
 * Return: the value of the environment variable
 */

char *_getenv(const char *name, char **environment)
{
	int i = 0, j = 0, diff = 0, l = 0;
	const char *s = name;
	char *ret;
	char **environment1 = environment;

	while (environment1[i] != NULL)
	{
		j = 0;
		diff = 0;
		while (environment1[i][j] != '=')
		{
			if (environment1[i][j] != s[j])
			{
				diff++;
				break;
			}
			j++;
		}
		if (diff == 0)
			break;
		i++;
	}
	if (diff == 0)
	{
		ret = malloc(strlen(environment1[i]));
		while (environment1[i][j + 1] != '\0')
		{
			ret[l] = environment1[i][j + 1];
			j++;
			l++;
		}
		ret[l] = '\0';
	}
	else
	{
		write(2, "Environment variable not found.\n", 31);
		exit(0);
	}
	return (ret);
	free(ret);
}

/**
 * path_dir - function4 to get the directories in path into a linked list
 *
 * @environment: array of environment variables
 *
 * Return: a apointer to the first element of the linked list
 */

dir_list *path_dir(char **environment)
{
	char *s, *s1, *line;
	int len = 0;
	dir_list *first;
	dir_list *head;
	char **environment1 = environment;

	s = _getenv("PATH", environment1);
	s1 = s;
	while (*s1 != '\0')
	{
		if (*s1 == 58)
		{
			len++;
		}
		s1++;
	}
	line = strtok(s, ":");
	first = malloc(strlen(line) + sizeof(dir_list));
	first->dir = line;
	first->next = NULL;
	head = first;
	while (len != 0)
	{
		line = strtok(NULL, ":");
		head = add_node(head, line);
		len--;
	}
	return (head);
	free(first);
}

/**
 * add_node - function5 to add a node to a linked list
 *
 * @head: pointer to the first element of the linked list;
 * @node: value of node to be added
 *
 * Return: pointer to the first element to the list that includes the new node
 */

dir_list *add_node(dir_list *head, char *node)
{
	dir_list *tail;
	dir_list *h;
	char *line;

	h = head;
	line = node;
	tail = malloc(sizeof(node) + sizeof(dir_list));
	tail->dir = line;
	tail->next = NULL;
	while (h->next != NULL)
	{
		h = h->next;
	}
	h->next = tail;
	return (head);
	free(tail);
}
