#include "my_ls.h"

static void switch_ls(t_ls *ls)
{
	if (ls->flags & FLG_LWR_D)
		flag_dir(ls);
	else if (ls->flags & FLG_UPR_R)
//		flag_recursive(ls);
	else
		usual(ls);
}

int 		main(int ac, char **av)
{
	t_ls	*ls;
	int		status;

	ls = init_ls(ac, av);
//	test_heap(ls);
	switch_ls(ls);
	status = ls->exit;
//	free_all(ls);
	return (status);
}
