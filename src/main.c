#include "my_ls.h"

int 	main(int ac, char **av)
{
	t_ls	*ls;

	ls = init_ls(ac, av);
	work_ls(ls);
	return (0);
}
