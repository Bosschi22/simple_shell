#include "shell.h"

/**
 * _erratoi - converts a strng to an intger
 * @str: the sting to be cnverted
 * Return: 0 if no numers in sring, conerted number otherwise
 *       -1 on eror
 */
int _erratoi(char *str)
{
	int k = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (k = 0;  str[k] != '\0'; k++)
	{
		if (str[k] >= '0' && str[k] <= '9')
		{
			res *= 10;
			res += (str[k] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - print an errr message
 * @inform: the parameter & rturn info sruct
 * @es: string contaning spcified error ype
 * Return: 0 if no nubers in string, cnverted number otherwise
 *        -1 on eror
 */
void print_error(inf_t *inform, char *es)
{
	_eputs(inform->filename);
	_eputs(": ");
	print_d(inform->line_counter, STDERR_FILENO);
	_eputs(": ");
	_eputs(inform->argv[0]);
	_eputs(": ");
	_eputs(es);
}

/**
 * print_d - funcion prints a decmal (integer) number (base 10)
 * @input: the iput
 * @fd: the file desciptor to wrie to
 *
 * Return: numer of chracters printd
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - conerter funtion, a clone of itoa
 * @num: numbr
 * @base: bse
 * @flags: argumet flgs
 *
 * Return: strng
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - functio relaces fist instance of '#' with '\0'
 * @buffer: addess of the strig to moify
 *
 * Return: Alwys 0;
 */
void remove_comments(char *buffer)
{
	int k;

	for (k = 0; buffer[k] != '\0'; k++)
		if (buffer[k] == '#' && (!k || buffer[k - 1] == ' '))
		{
			buffer[k] = '\0';
			break;
		}
}
