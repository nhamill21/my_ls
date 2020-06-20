#include "my_ls.h"

t_heap	*get_stack(t_stack *stack)
{
	return (stack ? stack->data : NULL);
}

t_stack	*new_stack(t_heap *data)
{
	return ((t_stack *)ft_lstnew((void *)data));
}

void 	push_stack(t_stack **stack, t_stack *new)
{
	ft_lstadd((t_list **)stack, (t_list *)new);
}

void 	pop_stack(t_stack **stack)
{
	ft_lstdelone((t_list **)stack);
}