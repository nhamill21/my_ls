#include "my_ls.h"

char 	*ft_pathjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	l;
	size_t	l1;
	size_t	l2;
	char 	*str;

	l1 = strlen(s1);
	l2 = strlen(s2);
	l = l1 + l2;
	if (!(str = (char *)malloc(sizeof(char) * (l + 2))))
		return (NULL);
	i = 0;
	while (i < l1)
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	*(str + i) = '/';
	while (++i <= l)
		*(str + i) = *(s2 + i - l1 - 1);
	*(str + i) = '\0';
	return (str);
}
