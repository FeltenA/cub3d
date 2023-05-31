/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:08:43 by afelten           #+#    #+#             */
/*   Updated: 2023/05/31 17:08:46 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_array_len(void **array)
{
	int		i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
