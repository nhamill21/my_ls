#include "my_ls.h"

char	*get_file_out(char *str, unsigned flags)
{
	return (str);
}

char		**init_output(int size)
{
	char	**str;

	if (!(str = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	return (str);
}