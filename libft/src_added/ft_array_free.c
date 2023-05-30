
#include <stdlib.h>

void	ft_array_free(void **array, int len, void free_funct(void *))
{
	int		i;

	if (!array)
		return ;
	i = 0;
	while (i < len)
	{
		if (array[i])
			free_funct(array[i]);
		i++;
	}
	free(array);
}
