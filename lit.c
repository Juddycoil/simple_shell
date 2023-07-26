#include "main.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
* token_len - to Locate the delimiter index marking the end
*             of  first token contained within a string.
* @str:  string to be searched.
* @delim: delimiter character.
*
* Return:  delimiter index marking the end of
*          intitial token pointed to be str.
*/
int token_len(char *str, char *delim)
{
int index = 0, len = 0;

while (*(str + index) && *(str + index) != *delim)
{
len++;
index++;
}

return (len);
}

/**
* count_tokens - to Count  number of delimited
*                word contained within a string.
* @str:  string to be searched.
* @delim: delimiter character.
*
* Return:  number of words contained within str.
*/
int count_tokens(char *str, char *delim)
{
int index, tokens = 0, len = 0;

for (index = 0; *(str + index); index++)
len++;

for (index = 0; index < len; index++)
{
if (*(str + index) != *delim)
{
tokens++;
index += token_len(str + index, delim);
}
}

return (tokens);
}

/**
* _strtok - Tokenizes  string.
* @line:  string.
* @delim: delimiter character to tokenize the string by.
*
* Return:  point to an array containing the tokenized words.
*/
char **_strtok(char *line, char *delim)
{
char **ptr;
int index = 0, tokens, n, letters, k;

tokens = count_tokens(line, delim);
if (tokens == 0)
return (NULL);

ptr = malloc(sizeof(char *) * (tokens + 2));
if (!ptr)
return (NULL);

for (n = 0; n < tokens; n++)
{
while (line[index] == *delim)
index++;

letters = token_len(line + index, delim);

ptr[t] = malloc(sizeof(char) * (letters + 1));
if (!ptr[n])
{
for (index -= 1; index >= 0; index--)
free(ptr[index]);
free(ptr);
return (NULL);
}

for (k = 0; k < letters; k++)
{
ptr[n][k] = line[index];
index++;
}

ptr[n][k] = '\0';
}
ptr[n] = NULL;
ptr[n + 1] = NULL;

return (ptr);
}
