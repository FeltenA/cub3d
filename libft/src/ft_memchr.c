/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:55:44 by afelten           #+#    #+#             */
/*   Updated: 2022/05/04 13:30:47 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*chr;
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(((unsigned char *)s) + i) == (unsigned char)c)
		{
			chr = ((unsigned char *)s) + i;
			return (chr);
		}
		i++;
	}
	return (0);
}
