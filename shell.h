#ifndef SHELL_H
#define SHELL_H

/**
 * struct dir_list - linked list to hold directories
 *
 * @dir: directory name
 * @next: pointer to next node holding next directory
 *
 */

typedef struct dir_list
{
char *dir;
struct dir_list *next;
} dir_list;

int get_strings(char *str);
int exit_code(char *i);
char *_getenv(const char *name, char **environment);
dir_list *path_dir(char **environment);
dir_list *add_node(dir_list *head, char *node);
void print_list(dir_list *head);
char *join(char *dir, char *com);
char *fix_string(char *str);
char *get_dir(dir_list *argument, char **environment);
dir_list *get_arg_link(char *input);
void execute_command(char *arg, dir_list *command, char *input);
int check_env(char *input, char **environment);


#endif
