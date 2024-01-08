#include "shell.h"

/**
 * is_cmd - determines if a file is an executab
 * @inform: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(inf_t *inform, char *path)
{
	struct stat st;

	(void)inform;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstring: the PATH string
 * @begin: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstring, int begin, int stop)
{
	static char buffer[1024];
	int i = 0, z = 0;

	for (z = 0, i = begin; i < stop; i++)
		if (pathstring[i] != ':')
			buffer[z++] = pathstring[i];
	buffer[z] = 0;
	return (buffer);
}

/**
 * find_path - finds this cmd in the PATH string
 * @inform: the info struct
 * @pathstring: the PATH string
 * @command: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(inf_t *inform, char *pathstring, char *command)
{
	int v = 0, current_pos = 0;
	char *path;

	if (!pathstring)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_cmd(inform, command))
			return (command);
	}
	while (1)
	{
		if (!pathstring[v] || pathstring[v] == ':')
		{
			path = dup_chars(pathstring, current_pos, v);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_cmd(inform, path))
				return (path);
			if (!pathstring[v])
				break;
			current_pos = v;
		}
		v++;
	}
	return (NULL);
}
