#include "my_ls.h"

static void	sift_down(t_heap *heap, int (*func)(const char *, const char *), int left, int right)
{
	char	*tmp;
	int		child;
	int		parent;

	parent = 0;
	child = (func(*(heap->arr + left), *(heap->arr + right)) > 0 ? left : right);
	while (func(*(heap->arr + parent), *(heap->arr + child)) < 0)
	{
		tmp = *(heap->arr + parent);
		*(heap->arr + parent) = *(heap->arr + child);
		*(heap->arr + child) = tmp;
		parent = child;
		left = (2 * parent + 1 < heap->last ? 2 * parent + 1 : parent);
		right = (2 * parent + 2 < heap->last ? 2 * parent + 2 : parent);
		child = (func(*(heap->arr + left), *(heap->arr + right)) > 0 ? left : right);
	}
}

static void	sift_up(t_heap *heap, int (*func)(const char *, const char *))
{
	char	*tmp;
	int		child;
	int		parent;

	if ((child = heap->last - 1) == heap->first)
		return ;
	while ((parent = (child % 2 ? child / 2 : child / 2 - 1)) >= 0 && func(*(heap->arr + parent), *(heap->arr + child)) < 0)
	{
		tmp = *(heap->arr + parent);
		*(heap->arr + parent) = *(heap->arr + child);
		*(heap->arr + child) = tmp;
		child = parent;
	}
}

void		heap_sort(t_heap *heap, int (*func)(const char *, const char *))
{
	char	*tmp;
	int		last;

	last = heap->last;
	while (heap->last > heap->first)
	{
		tmp = *(heap->arr + heap->last - 1);
		*(heap->arr + heap->last - 1) = *(heap->arr);
		*(heap->arr) = tmp;
		if (--heap->last == heap->first + 1)
			break ;
		sift_down(heap, func, (2 * heap->first + 1 < heap->last ? 2 * heap->first \
					+ 1 : heap->first), (2 * heap->first + 2 < heap->last ? \
					2 * heap->first + 2 : heap->first));
	}
	heap->last = last;
}

int 		add_heap_elem(t_heap **heap, char *data, int (*func)(const char *, const char *))
{
	if (heap && data)
	{
		if (!*heap)
		{
			if (!(*heap = (t_heap *)malloc(sizeof(t_heap))))
				return (1);
			(*heap)->first = 0;
			(*heap)->last = 1;
			(*heap)->size = START_HEAP_SIZE;
			if (!((*heap)->arr = (char **)malloc(sizeof(char *) * (*heap)->size)))
			{
				free(*heap);
				return (1);
			}
			(*heap)->out = NULL;
			*((*heap)->arr) = data;
		}
		else
		{
			if ((*heap)->last == (*heap)->size)
			{
				(*heap)->size *= COEF_HEAP_INC;
				(*heap)->arr = realloc((*heap)->arr, (*heap)->size * sizeof(char *));
			}
			*((*heap)->arr + (*heap)->last) = data;
			(*heap)->last++;
		}
		sift_up(*heap, func);
	}
	return (0);
}

char 		*get_heap_max(t_heap *heap)
{
	if (heap->first == heap->last)
		return (NULL);
	heap->first++;
	return (*(heap->arr + heap->first - 1));
}

char 		*get_heap_min(t_heap *heap)
{
	if (heap->last == heap->first)
		return (NULL);
	heap->last--;
	return (*(heap->arr + heap->last));
}
