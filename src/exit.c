#include "my_ls.h"

int		ft_exit(int status, t_ls *ls)
{
	if (ls)
		free(ls);
	return (status);
}