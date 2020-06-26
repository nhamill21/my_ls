#include "my_ls.h"

static int		allowed_name(char *name, unsigned flags)
{
	return (1);
}

static void		get_name(t_heap *heap)
{
	char	*s;

	if (!heap || !heap->arr || !*heap->arr)
		return ;
	if (!(s = strrchr(*heap->arr, '/')))
		printf(".:\n");
	else
	{
		*s = '\0';
		printf("%s:\n", *heap->arr);
		*s = '/';
	}
}

static int		wrong_dir(char *name)
{
	size_t	len;

	len = strlen(name);
	if (len > 1 && *(name + len - 1) == '.' && *(name + len - 2) == '/')
		return (1);
	if (len > 2 && *(name + len - 1) == '.' && *(name + len - 2) == '.' && *(name + len - 3) == '/')
		return (1);
	return (0);
}



static t_heap	*work_dir(char *name, t_ls *ls)
{
	t_heap			*new;
	DIR 			*dr;
	struct dirent	*dir;

	new = NULL;
	if ((dr = opendir(name)))
	{
		while ((dir = readdir(dr)))
			if (allowed_name(dir->d_name, ls->flags))
				if (add_heap_elem(&new, ft_pathjoin(name, dir->d_name), ls->func))
					ft_exit(4, ls);
		closedir(dr);
	}
	else if (errno != ENOTDIR)
	{
		perror(name);
		ls->exit = MINOR_PROBLEMS;
		return (NULL);
	}
	return (new);
}

void		dir_as_file(t_heap *heap, t_ls *ls)
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

void		first_level_dirs(t_ls *ls)
{
	char		*file;
	t_heap		*level_cur;
	t_heap		*level_new;
	t_stack		*stack_new;

	stack_new = NULL;
	level_cur = get_stack(ls->stack);
	while ((file = get_heap_max(level_cur)))
	{
		if ((level_new = work_dir(file, ls))) {
			push_stack(&stack_new, new_stack(level_new));
		}
	}
	pop_stack(&ls->stack);
	if (stack_new)
	{
		push_stack(&ls->stack, stack_new);
		stack_new = NULL;
	}
}

void			non_recurs(t_ls *ls)
{
	char		*file;
	t_heap		*level_cur;
	t_heap		*level_new;
	t_stack		*stack_new;

	stack_new = NULL;
	while ((level_cur = get_stack(ls->stack)))
	{
		get_name(level_cur);
		dir_as_file(level_cur, ls);
		printf(ls->stack->next || stack_new ? "\n" : "");
		pop_stack(&ls->stack);
		if (stack_new)
		{
			push_stack(&ls->stack, stack_new);
			stack_new = NULL;
		}
	}
}

void			recurs(t_ls *ls)
{
	char		*file;
	t_heap		*level_cur;
	t_heap		*level_new;
	t_stack		*stack_new;

	stack_new = NULL;
	while ((level_cur = get_stack(ls->stack)))
	{
		while ((file = get_heap_max(level_cur)))
		{
			if (wrong_dir(file))
				continue ;
			if ((level_new = work_dir(file, ls)))
				push_stack(&stack_new, new_stack(level_new));
		}
		get_name(level_cur);
		dir_as_file(level_cur, ls);
		printf(ls->stack->next || stack_new ? "\n" : "");
		pop_stack(&ls->stack);
		if (stack_new)
		{
			push_stack(&ls->stack, stack_new);
			stack_new = NULL;
		}
	}
}