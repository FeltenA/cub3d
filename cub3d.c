
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char **array = malloc(sizeof(char *) * 2);
	array[0] = ft_strdup("test1");
	array = ft_realloc(array, sizeof(char *) * 2, sizeof(char *) * 3);
	array[1] = ft_strdup("test2");
	array[2] = 0;
	for (int i = 0; i < 2; i++)
		printf("%s\n", array[i]);
	ft_array_free((void **)array, 2, &free);
}