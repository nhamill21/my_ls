#include "my_ls.h"

void		print_out(t_heap *heap, unsigned flags)
{
	size_t	i;

	i = 0;
	while (i < heap->last)
	{
		if (*(heap->out + i))
			printf("%s  ", *(heap->out + i));
		i++;
	}
	printf("\n");
}