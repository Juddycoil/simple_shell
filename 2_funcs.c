#include "main.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
* _strchr - to Locate a character in a string.
* @s:  string to be searched.
* @c:  character to be located.
*
* Return: If c is found - a point to the first occurence.
*         If c is not found - NULL.
*/
char *_strchr(char *s, char c)
{
int index;

for (index = 0; s[index]; index++)
{
if (s[index] == c)
return (s + index);
}

return (NULL);
}

/**
* _strspn - Get  length of a prefix substring.
* @s:  string to be searched.
* @accept: prefix to be measured.
*
* Return:  number of bytes in s which
*         consist only of bytes from accept.
*/
int _strspn(char *s, char *accept)
{
int bytes = 0;
int index;

while (*s)
{
for (index = 0; accept[index]; index++)
{
if (*s == accept[index])
{
bytes++;
break;
}
}
s++;
}
return (bytes);
}

/**
* _strcmp - to Compare two strings.
* @s1:  first string to be compared.
* @s2:  second string to be compared.
*
* Return: Positive byte difference if s1 > s2
*         0 if s1 = s2
*         Negative byte difference if s1 < s2
*/
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2 && *s1 == *s2)
{
s1++;
s2++;
}

if (*s1 != *s2)
return (*s1 - *s2);

return (0);
}

/**
* _strncmp - Compare two strings.
* @s1: Point to a string.
* @s2: Point to a string.
* @n:  first n bytes of the strings to compare.
*
* Return: Less than 0 if s1 is shorter than s2.
*         0 if s1 and s2 match.
*         Greater than 0 if s1 is longer than s2.
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
size_t c;

for (c = 0; s1[c] && s2[c] && c < n; c++)
{
if (s1[c] > s2[c])
return (s1[c] - s2[c]);
else if (s1[c] < s2[c])
return (s1[c] - s2[c]);
}
if (c == n)
return (0);
else
return (-15);
}
