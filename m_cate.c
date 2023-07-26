#include "main.h"

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
* get_location - to Locate the command in the PATH.
* @command:  to locate the command.
*
* Return: If an error occurs or a command cannot be located - NULL.
*         Otherwise - full pathname of the command.
*/
char *get_location(char *command)
{
char **path, *temp;
list_t *dirs, *head;
struct stat st;

path = _getenv("PATH");
if (!path || !(*path))
return (NULL);

dirs = get_path_dir(*path + 5);
head = dirs;

while (dirs)
{
temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
if (!temp)
return (NULL);

_strcpy(temp, dirs->dir);
_strcat(temp, "/");
_strcat(temp, command);

if (stat(temp, &st) == 0)
{
free_list(head);
return (temp);
}

dirs = dirs->next;
free(temp);
}

free_list(head);

return (NULL);
}

/**
* fill_path_dir - Copy the path but also replaces leading/sandwiched/trailing
*   colons (:) with current working directory.
* @path:  colon-separated list of the directories.
*
* Return:  copy of path with any leading/sandwiched/trailing colons replaced
*   with current working directory.
*/
char *fill_path_dir(char *path)
{
int m, length = 0;
char *path_copy, *pwd;

pwd = *(_getenv("PWD")) + 4;
for (m = 0; path[m]; m++)
{
if (path[m] == ':')
{
if (path[m + 1] == ':' || m == 0 || path[m + 1] == '\0')
length += _strlen(pwd) + 1;
else
length++;
}
else
length++;
}
path_copy = malloc(sizeof(char) * (length + 1));
if (!path_copy)
return (NULL);
path_copy[0] = '\0';
for (m = 0; path[m]; m++)
{
if (path[m] == ':')
{
if (m == 0)
{
_strcat(path_copy, pwd);
_strcat(path_copy, ":");
}
else if (path[m + 1] == ':' || path[m + 1] == '\0')
{
_strcat(path_copy, ":");
_strcat(path_copy, pwd);
}
else
_strcat(path_copy, ":");
}
else
{
_strncat(path_copy, &path[m], 1);
}
}
return (path_copy);
}

/**
* get_path_dir - Tokenizes the colon-separated list of
*                directories into  list_s linked list.
* @path:  colon-separated list of directories.
*
* Return: the pointer to  initialized linked list.
*/
list_t *get_path_dir(char *path)
{
int index;
char **dirs, *path_copy;
list_t *head = NULL;

path_copy = fill_path_dir(path);
if (!path_copy)
return (NULL);
dirs = _strtok(path_copy, ":");
free(path_copy);
if (!dirs)
return (NULL);

for (index = 0; dirs[index]; index++)
{
if (add_node_end(&head, dirs[index]) == NULL)
{
free_list(head);
free(dirs);
return (NULL);
}
}

free(dirs);

return (head);
}
