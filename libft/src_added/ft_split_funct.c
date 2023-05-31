/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_funct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:09:25 by afelten           #+#    #+#             */
/*   Updated: 2023/05/31 17:09:28 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_str_num(char const *s, int (*funct)(char))
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (!(*funct)(s[i]))
		{
			num++;
			while (s[i] && !(*funct)(s[i]))
				i++;
		}
		else
			i++;
	}
	return (num);
}

static char	*cpy_str(const char **s, int (*funct)(char))
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	while ((*s)[len] && !(*funct)((*s)[len]))
		len++;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (**s && !(*funct)(**s))
	{
		str[i] = **s;
		(*s)++;
		i++;
	}
	str[i] = 0;
	return (str);
}

static void	free_funct(char **sstr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(sstr[i]);
		i++;
	}
	free(sstr);
}

char	**ft_split_funct(char const *s, int (*funct)(char))
{
	char	**sstr;
	int		j;

	sstr = malloc((get_str_num(s, funct) + 1) * sizeof(char *));
	if (!sstr)
		return (0);
	j = 0;
	while (*s)
	{
		if (!(*funct)(*s))
		{
			sstr[j] = cpy_str(&s, funct);
			if (!sstr[j])
			{
				free_funct(sstr, j);
				return (0);
			}
			j++;
		}
		else
			s++;
	}
	sstr[j] = 0;
	return (sstr);
}
