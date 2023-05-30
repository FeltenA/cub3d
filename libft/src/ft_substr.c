/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:41:17 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 19:16:42 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*str;

	i = 0;
	size = 0;
	while (s[i])
		i++;
	if (i < start)
		size = 0;
	else if (i < start + len)
		size = i - start;
	else
		size = len;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (0);
	j = -1;
	while (start + ++j < start + len && start + j < i)
		str[j] = s[start + j];
	str[j] = 0;
	return (str);
}
