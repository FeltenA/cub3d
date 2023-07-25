
void	ft_array_exec(void **array, int len, void funct(void *))
{
	int		i;

	if (!array)
		return ;
	i = 0;
	while (i < len)
	{
		funct(array[i]);
		i++;
	}
}
