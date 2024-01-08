#include "shell.h"

/**
 * interactive - returns true if shell is interactive
 * @inform: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(inf_t *inform)
{
	return (isatty(STDIN_FILENO) && inform->readfd <= 2);
}

/**
 * is_delim - checks if char is a delimeter
 * @ch: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 *_isalpha - cheks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int z, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (z = 0;  str[z] != '\0' && flag != 2; z++)
	{
		if (str[z] == '-')
			sign *= -1;

		if (str[z] >= '0' && str[z] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str[z] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
