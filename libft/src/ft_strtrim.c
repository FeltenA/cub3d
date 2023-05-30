/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:55:56 by afelten           #+#    #+#             */
/*   Updated: 2022/05/04 14:48:55 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_new_len(char const *s1, char const *set)
{
	int	i;
	int	len;
	int	save;

	i = 0;
	len = 0;
	while (in_set(s1[i], set))
		i++;
	while (s1[i])
	{
		if (in_set(s1[i], set))
		{
			save = i;
			while (in_set(s1[i], set))
				i++;
			save = i - save;
			if (!s1[i])
				break ;
			len += save;
		}
		len++;
		i++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	len = get_new_len(s1, set);
	str = malloc((get_new_len(s1, set) + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (in_set(s1[i], set))
		i++;
	while (j < len)
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	str[j] = 0;
	return (str);
}
