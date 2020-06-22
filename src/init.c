#include "my_ls.h"

static void set_flags(char *str, unsigned *flags)
{
	char		*s;
	size_t		i;
	unsigned	flag;

	i = 1;
	while (*(str + i) && !(*flags & FLAG_FAIL) && !(*flags & FLG_LWR_H))
	{
		flag = ((s = strchr(FLAGS, *(str + i))) ? \
						1 << (s - FLAGS) : FLAG_FAIL);
		if (flag & FLAGS_SORT)
			*flags = *flags & FLAG_TO_NULL_SORT | flag;
		else if (flag & FLAG_LONG_LIST)
			*flags = *flags & FLAG_TO_NULL_MANY_COLS | flag | FLG_UPR_1;
		else if (flag & FLAG_MANY_COLS)
			*flags = *flags & FLAG_TO_NULL_ONE_COL | flag | FLG_UPR_C;
		else if (flag & FLAG_TIME)
			*flags = *flags & FLAG_TO_NULL_TIME | flag;
		else if (flag & FLG_LWR_M)
			*flags = *flags & FLAG_TO_NULL_EXCEPT_M | flag | FLG_UPR_1;
		else
			*flags |= flag;
		i++;
	}
}

static void	search_flags(int ac, char **av, unsigned *flags)
{
	size_t		i;

	i = 1;
	while (i < ac)
	{
		if (*(av + i) && *(*(av + i)) == '-' && *(*(av + i) + 1))
		{
			if (*(*(av + i) + 1) == '-')
			{
				*(av + i) = NULL;
				break ;
			}
			set_flags(*(av + i), flags);
			if (*flags & FLAG_FAIL)
				printf("%s%s%s\n", ERR_FLAG_FAIL, *(av + i), ERR_HELP);
			if (*flags & FLG_LWR_H)
				printf("%s\n", MGS_HELP);
			if ((*flags & FLAG_FAIL) || (*flags & FLG_LWR_H))
				break ;
			*(av + i) = NULL;
		}
		i++;
	}
}

static t_ls	*get_fresh_ls(void)
{
	t_ls	*ls;

	ls = NULL;
	if (!(ls = (t_ls *)malloc(sizeof(t_ls))))
		return (NULL);
	if (!(ls->stack = (t_stack *)malloc(sizeof(t_stack))))
	{
		free(ls);
		return (NULL);
	}
	ls->exit = 0;
	ls->stack = NULL;
	ls->flags = FLAG_DEFAULT;
	return (ls);
}

static void	set_sort_func(t_ls *ls)
{
	if (ls->flags & FLG_LWR_V)
		ls->func = strcmp;
	else if (ls->flags & FLG_LWR_T)
		ls->func = NULL;
	else if (ls->flags & FLG_UPR_S)
		ls->func = NULL;
	else if (ls->flags & FLG_LWR_F)
		ls->func = NULL;
	else if (ls->flags & FLG_LWR_Y)
		ls->func = NULL;
}

static void	set_first_args(int ac, char **av, t_ls *ls)
{
	size_t	i;
	t_heap	*heap;

	i = 1;
	heap = NULL;
	while (i < ac)
	{
		if (*(av + i))
			if (add_heap_elem(&heap, *(av + i), ls->func))
				ft_exit(4, ls);
		i++;
	}
	if (!heap)
		if (add_heap_elem(&heap, ".", NULL))
			ft_exit(4, ls);
	push_stack(&ls->stack, new_stack(heap));
}

t_ls		*init_ls(int ac, char **av)
{
	t_ls	*ls;

	if (!(ls = get_fresh_ls()))
		ft_exit(1, NULL);
	search_flags(ac, av, &ls->flags);
	if (ls->flags & FLAG_FAIL)
		ft_exit(2, ls);
	if (ls->flags & FLG_LWR_H)
		ft_exit(3, ls);
	set_sort_func(ls);
	set_first_args(ac, av, ls);
	return (ls);
}