
#include <stdlib.h>

void	ft_free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
}