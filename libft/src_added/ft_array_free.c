/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:08:33 by afelten           #+#    #+#             */
/*   Updated: 2023/05/31 17:08:36 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
