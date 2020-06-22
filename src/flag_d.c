#include "my_ls.h"

void		flag_dir(t_ls *ls)
{
	size_t	i;
	t_heap	*heap;

	heap = get_stack(ls->stack);
	if (!(heap->out = init_output(heap->last)))
		ft_exit(6, ls);
	if ((i = heap->last))
	{
		while (i--)
		{
			if (!(*(heap->out + i) = get_file_out(*(heap->arr + i), ls->flags)))
				ls->exit = SERIOUS_TROUBLE; // макрос, тернарник?
		}
		print_out(heap, ls->flags);
	}
}