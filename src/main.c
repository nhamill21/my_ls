#include "my_ls.h"

static void type_of_ls(t_ls *ls)
{
	dir_as_file(get_stack(ls->stack), ls);
	if (get_stack(ls->stack) && get_stack(ls->stack->next))
		printf("\n");
	pop_stack(&ls->stack);
	if (!(ls->flags & FLG_LWR_D))
	{
		first_level_dirs(ls);
		(ls->flags & FLG_UPR_R ? recurs(ls) : non_recurs(ls));
	}
}

int 		main(int ac, char **av)
{
	t_ls	*ls;
	int		status;

	ls = init_ls(ac, av);
	type_of_ls(ls);
	status = ls->exit;
//	free_all(ls);
	return (status);
}
