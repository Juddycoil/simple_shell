#include "main.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
* _strlen - Returns the length of a string.
* @s: point to the characters string.
*
* Return:  length of the character string.
*/
int _strlen(const char *s)
{
int length = 0;

if (!s)
return (length);
for (length = 0; s[length]; length++)
;
return (length);
}

/**
* _strcpy - Copy  string pointed to by src, including 
*           terminating null byte, to  buffer pointed by des.
* @dest: Point to  destination of copied string.
* @src: Point to the src of the source string.
*
* Return: Pointe to dest.
*/
char *_strcpy(char *dest, const char *src)
{
size_t c;

for (c = 0; src[c] != '\0'; c++)
dest[c] = src[c];
dest[c] = '\0';
return (dest);
}

/**
* _strcat - to Concantenates two strings.
* @dest: Point to destination string.
* @src: Point to source string.
*
* Return: Point to destination string.
*/
char *_strcat(char *dest, const char *src)
{
char *destTemp;
const char *srcTemp;

destTemp = dest;
srcTemp =  src;

while (*destTemp != '\0')
destTemp++;

while (*srcTemp != '\0')
*destTemp++ = *srcTemp++;
*destTemp = '\0';
return (dest);
}

/**
* _strncat - to Concantenates two strings where n num
*            of byte are copied from source.
* @dest: Point to destination string.
* @src: Point to source string.
* @n: n bytes to copy from src.
*
* Return: Point to destination string.
*/
char *_strncat(char *dest, const char *src, size_t n)
{
size_t dest_len = _strlen(dest);
size_t c;

for (c = 0; c < n && src[c] != '\0'; c++)
dest[dest_len + c] = src[c];
dest[dest_len + c] = '\0';

return (dest);
}
