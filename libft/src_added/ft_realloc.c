
#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t oldsize, size_t size)
{
	void	*new;

	if (size <= oldsize)
		return (ptr);
	new = malloc(size);
	if (!new)
		return (0);
	ft_memcpy(new, ptr, oldsize);
	if (ptr)
		free(ptr);
	return (new);
}