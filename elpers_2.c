#include "main.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - the Partition a line read from standard input as needed.
 * @line:  point to a line read from standard input.
 * @read:  length of line.
 *
 * Description: the Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
char *old_line, *new_line;
char previous, current, next;
size_t c, o;
ssize_t new_len;

new_len = get_new_len(*line);
if (new_len == read - 1)
return;
new_line = malloc(new_len + 1);
if (!new_line)
return;
o = 0;
old_line = *line;
for (c = 0; old_line[c]; c++)
{
current = old_line[c];
next = old_line[c + 1];
if (c != 0)
{
previous = old_line[c - 1];
if (current == ';')
{
if (next == ';' && previous != ' ' && previous != ';')
{
new_line[o++] = ' ';
new_line[o++] = ';';
continue;
}
else if (previous == ';' && next != ' ')
{
new_line[o++] = ';';
new_line[o++] = ' ';
continue;
}
if (previous != ' ')
new_line[o++] = ' ';
new_line[o++] = ';';
if (next != ' ')
new_line[o++] = ' ';
continue;
}
else if (current == '&')
{
if (next == '&' && previous != ' ')
new_line[o++] = ' ';
else if (previous == '&' && next != ' ')
{
new_line[o++] = '&';
new_line[o++] = ' ';
continue;
}
}
else if (current == '|')
{
if (next == '|' && previous != ' ')
new_line[o++]  = ' ';
else if (previous == '|' && next != ' ')
{
new_line[o++] = '|';
new_line[o++] = ' ';
continue;
}
}
}
else if (current == ';')
{
if (c != 0 && old_line[c - 1] != ' ')
new_line[o++] = ' ';
new_line[o++] = ';';
if (next != ' ' && next != ';')
new_line[o++] = ' ';
continue;
}
new_line[o++] = old_line[c];
}
new_line[o] = '\0';

free(*line);
*line = new_line;
}

/**
 * get_new_len - to Get the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line:  line to check.
 *
 * Return:  new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
size_t c;
ssize_t new_len = 0;
char current, next;

for (c = 0; line[c]; c++)
{
current = line[c];
next = line[c + 1];
if (current == '#')
{
if (c == 0 || line[c - 1] == ' ')
{
line[c] = '\0';
break;
}
}
else if (c != 0)
{
if (current == ';')
{
if (next == ';' && line[c - 1] != ' ' && line[c - 1] != ';')
{
new_len += 2;
continue;
}
else if (line[c - 1] == ';' && next != ' ')
{
new_len += 2;
continue;
}
if (line[c - 1] != ' ')
new_len++;
if (next != ' ')
new_len++;
}
else
logical_ops(&line[c], &new_len);
}
else if (current == ';')
{
if (c != 0 && line[c - 1] != ' ')
new_len++;
if (next != ' ' && next != ';')
new_len++;
}
new_len++;
}
return (new_len);
}
/**
* logical_ops - to Check the line for logical operators "||" or "&&".
* @line: to point to the character to check in the line.
* @new_len: Point to new_len in get_new_len function.
*/
void logical_ops(char *line, ssize_t *new_len)
{
char previous, current, next;

previous = *(line - 1);
current = *line;
next = *(line + 1);

if (current == '&')
{
if (next == '&' && previous != ' ')
(*new_len)++;
else if (previous == '&' && next != ' ')
(*new_len)++;
}
else if (current == '|')
{
if (next == '|' && previous != ' ')
(*new_len)++;
else if (previous == '|' && next != ' ')
(*new_len)++;
}
}
