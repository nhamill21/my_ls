#include "my_ls.h"

t_heap	*get_stack(t_stack *stack)
{
	return (stack ? stack->data : NULL);
}

void 	push_stack(t_stack **stack, void *data)
{
	ft_lstadd((t_list **)stack, ft_lstnew((void *)data));
}

void 	pop_stack(t_stack **stack)
{
	ft_lstdelone((t_list **)stack);
}