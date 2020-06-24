#include "my_ls.h"

static int		allowed_name(char *name, unsigned flags)
{
	return (1);
}

static t_heap	*get_files(char *name, t_ls *ls)
{
	t_heap			*heap;
	DIR 			*dr;
	struct dirent	*dir;

	heap = NULL;
	if ((dr = opendir(name)))
	{
		while ((dir = readdir(dr)))
			if (allowed_name(dir->d_name, ls->flags))
				if (add_heap_elem(&heap, strdup(dir->d_name), ls->func))
					ft_exit(4, ls);
		closedir(dr);
	}
	return (heap);
}

static void		work_with_dir(t_ls *ls)
{
	size_t	i;
	t_heap	*heap;

	if ((heap = get_stack(ls->stack)))
	{
		if ((i = heap->last))
		{
			while (i--)
			{
				printf(heap->last != 1 ? "%s:\n" : "", *(heap->arr + i));
				flag_dir(get_files(*(heap->arr + i), ls), ls);
				printf(i ? "\n" : "");
			}
		}
	}
}

void			wo_dir_an_recursive(t_ls *ls)
{
	flag_dir(get_stack(ls->stack), ls);
	if (get_stack(ls->stack) && get_stack(ls->stack->next))
		printf("\n");
	pop_stack(&ls->stack);
	work_with_dir(ls);
}