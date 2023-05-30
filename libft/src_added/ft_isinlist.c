
int	ft_isinlist(char c, const char *list)
{
	while (*list)
    {
        if (*list == c)
            return (1);
        list++;
    }
    return (0);
}