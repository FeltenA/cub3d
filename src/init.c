/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:11:14 by afelten           #+#    #+#             */
/*   Updated: 2023/05/31 17:11:16 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->mlx_win = mlx_new_window(
			data->mlx, data->width, data->height, "cub3d");
	if (!data->mlx_win)
	{
		free_data(data);
		return (0);
	}
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

	data->mlx = 0;
	data->mlx_win = 0;
	data->img = 0;
	data->height = RES_HEIGHT;
	data->width = RES_WIDTH;
	data->map = 0;
	data->max_x = 0;
	data->max_y = 0;
	data->c_color = -1;
	data->f_color = -1;
	i = -1;
	while (++i < TEXT_NBR)
	{
		data->f_imgs[i].img.img = 0;
		data->f_imgs[i].img.addr = 0;
	}
	return (init_mlx(data));
}
