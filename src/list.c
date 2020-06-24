#include "my_ls.h"

t_list	*ft_lstnew(void *data)
{
	t_list		*new;

	new = NULL;
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

void 	ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (new)
	{
		if (alst && *alst)
		{
			tmp = new;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = *alst;
		}
		*alst = new;
	}

}

void 	ft_lstdelone(t_list **del)
{
	t_list	*tmp;

	if (del)
	{
		tmp = *del;
		*del = (*del)->next;
		free(tmp);
		tmp = NULL;
	}
}
