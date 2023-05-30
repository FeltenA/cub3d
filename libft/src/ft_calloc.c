/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:14:07 by afelten           #+#    #+#             */
/*   Updated: 2022/05/04 13:43:29 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	tsize;
	void	*array;

	tsize = size * nmemb;
	if (size != 0 && tsize / size != nmemb)
		return (0);
	array = malloc(tsize);
	if (!array)
		return (0);
	i = -1;
	while (++i < tsize)
		*((char *)array + i) = 0;
	return (array);
}
