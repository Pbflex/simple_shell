#include "shell.h"

/**
* interactive - this returns true if shell is interactive mode
* @info: struct address
* Return: 1 if interactive mode or 0 if not interactive mode
*/

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delim - this checks if character is a delimeter
* @c: the char to check
* @delim: the delimeter string
* Return: 1 if true, 0 if false
*/

int is_delim(char c, char *delim)
{
	while (*delim)
	if (*delim++ == c)
	return (1);
	return (0);
}

/**
*_isalpha - this checks for alphabet character
*@c: The character to input
*Return: 1 if c is alphabet, 0 otherwise
*/

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	return (1);
	else
	return (0);
}

/**
*_atoi - this converts a string to an integer
*@s: the string to be converted
*Return: 0 if no numbers in string, converted number otherwise
*/

int _atoi(char *s)
{
	unsigned int answer = 0;
	int j, sign = 1, flag = 0, result;

	for (j = 0;  s[j] != '\0' && flag != 2; j++)
	{
	if (s[j] == '-')
	sign *= -1;

	if (s[j] >= '0' && s[j] <= '9')
		{
	flag = 1;
	answer *= 10;
	answer += (s[j] - '0');
	}
	else if (flag == 1)
	flag = 2;
	}

	if (sign == -1)
	result = -answer;
	else
	result = answer;

	return (result);
}
