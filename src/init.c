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

static int	add_files_dirs(char *name, t_heap **dirs, t_heap **files, t_ls *ls)
{
	DIR		*dr;

	errno = 0;
	if ((dr = opendir(name)))
	{
		closedir(dr);
		if (add_heap_elem((ls->flags & FLG_LWR_D ? files : dirs), strdup(name), ls->func))
			return (1);
	}
	else if (errno == ENOTDIR)
	{
		if (add_heap_elem(files, strdup(name), ls->func))
			return (1);
	}
	else
	{
		perror(name);
		ls->exit = SERIOUS_TROUBLE;
	}
	return (0);
}

static void	set_first_args(int ac, char **av, t_ls *ls)
{
	size_t	i;
	t_heap	*dirs;
	t_heap	*files;

	i = 1;
	dirs = NULL;
	files = NULL;
	while (i < ac)
	{
		if (*(av + i))
			if (add_files_dirs(*(av + i), &dirs, &files, ls))
			{
//				free_heap(dirs);
//				free_heap(files);
				ft_exit(4, ls);
			}
		i++;
	}
	if (!dirs && !files)
		if (add_heap_elem(&dirs, strdup("."), ls->func))
			ft_exit(4, ls);
	push_stack(&ls->stack, new_stack(dirs));
	push_stack(&ls->stack, new_stack(files));
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