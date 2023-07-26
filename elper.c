#include "main.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - to Free up the memory taken by args.
 * @args:  null-terminated double pointer containing commands/arguments.
 * @front: the  double point to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t c;

	for (c = 0; args[c] || args[c + 1]; c++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - to Get the current process ID.
 * Description: Open the stat file, a space-delimited file containing
 *              information about current process.  PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return:  current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t c = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[c] != ' ')
		c++;
	buffer[c] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Get  value corresponding to an environmental variable.
 * @beginning:  environmental variable to search for.
 * @len:  length of the environmental variable to search for.
 *
 * Return: If  variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - to Handle variable replacement.
 * @line: the double pointer containing the command and args.
 * @exe_ret: the pointer to  return the value of the last executed command.
 *
 * Description: Replace the $$ with the current PID, $? with the return value
 *               the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int m, o = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (m = 0; old_line[m]; m++)
	{
		if (old_line[m] == '$' && old_line[m + 1] &&
				old_line[m + 1] != ' ')
		{
			if (old_line[m + 1] == '$')
			{
				replacement = get_pid();
				o = m + 2;
			}
			else if (old_line[m + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				o = m + 2;
			}
			else if (old_line[m + 1])
			{
				/* extract the variable name to search for */
				for (o = m + 1; old_line[o] &&
						old_line[o] != '$' &&
						old_line[o] != ' '; o++)
					;
				len = o - (m + 1);
				replacement = get_env_value(&old_line[m + 1], len);
			}
			new_line = malloc(m + _strlen(replacement)
					  + _strlen(&old_line[o]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, m);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[o]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			m = -1;
		}
	}
}
