#include "my_ls.h"

char		*get_file_out(char *str, unsigned flags)
{
	char	*s;

	if (!(s = strrchr(str, '/')))
		return (str);
	return (s + 1);
}