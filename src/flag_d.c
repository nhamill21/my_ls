#include "my_ls.h"

void		flag_dir(t_heap *heap, t_ls *ls)
{
	size_t	i;
	char	**str;

	if (!heap)
		return ;
	if (!(heap->out = (char **)malloc(sizeof(char *) * heap->last)))
		ft_exit(6, ls);
	heap_sort(heap, ls->func);
	if ((i = heap->last))
	{
		while (i--)
		{
			if (!(*(heap->out + i) = get_file_out(*(heap->arr + i), ls->flags)))
				ft_exit(6, ls);
		}
		print_out(heap, ls->flags);
	}
}