#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*o;

	o = (char *)s;
	i = 0;
	while (i < n)
	{
		o[i] = 0;
		i++;
	}
}
