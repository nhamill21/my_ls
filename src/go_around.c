#include "my_ls.h"

t_heap	*parse_dir(t_heap *heap, int (*func)(const char *, const char *))
{
	return (NULL);
}

void 	work_ls(t_ls *ls)
{
	t_heap		*cur_level;
	t_heap		*new_level;

	while ((cur_level = get_stack(ls->stack)))
	{
		if ((new_level = parse_dir(cur_level, ls->func)))
			push_stack(&ls->stack, new_level);
		else
			pop_stack(&ls->stack);
	}
}
