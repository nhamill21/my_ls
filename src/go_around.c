#include "my_ls.h"

static t_heap	*parse_dir(t_heap *heap, unsigned flags, int (*func)(const char *, const char *))
{
	return (NULL);
}

void 			work_ls(t_ls *ls)
{
	char		*file;
	t_heap		*level_cur;
	t_heap		*level_new;
	t_stack		*stack_new;

	stack_new = NULL;
	while ((level_cur = get_stack(ls->stack)))
	{
		while ((file = get_heap_min(level_cur)))
		{
			if ((level_new = parse_dir(&level_cur, ls->func)))
				push_stack(&stack_new, new_stack(level_new));
		}
		pop_stack(&ls->stack);
		if (stack_new)
		{
			push_stack(&ls->stack, stack_new);
			stack_new = NULL;
		}
	}
}
