/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:11:34 by afelten           #+#    #+#             */
/*   Updated: 2023/05/31 17:11:35 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEX_NBR)
		if (data->f_imgs[i].img.img)
			mlx_destroy_image(data->mlx, data->f_imgs[i].img.img);
	if (data->map)
		ft_array_free((void **)data->map,
			ft_array_len((void **)data->map), &free);
	if (data->texture_pixels)
	{
		ft_array_free((void **)data->texture_pixels,
			ft_array_len((void **)data->texture_pixels), &free);
	}
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	close_window(t_data *data)
{
	free_data(data);
	exit(0);
}
