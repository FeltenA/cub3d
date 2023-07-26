/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:36:24 by qrolland          #+#    #+#             */
/*   Updated: 2023/07/06 14:39:02 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		raycasting(t_player *player, t_data *data);
void	init_ray(t_ray *ray);
void	draw_minimap(t_data *data, t_img *img);

static void	set_frame_pixel(t_data *data, t_img *image, int x, int y)
{
	if (x > data->win_width || y > data->win_height)
		return ;
	if (data->texture_pixels[y][x] > 0)
		draw_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		draw_pixel(image, x, y, data->c_color);
	else if (y < data->win_height - 1)
		draw_pixel(image, x, y, data->f_color);
}

static void	display_frame(t_data *data)
{
	t_img	img;
	int		x;
	int		y;

	img.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!img.img)
		return ;
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
			&img.line_len, &img.endian);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_pixel(data, &img, x, y);
			x++;
		}
		y++;
	}
	draw_minimap(data, &img);
	mlx_put_image_to_window(data->mlx, data->mlx_win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
}

static void	reset_pixels(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->win_height)
	{
		j = -1;
		while (++j < data->win_width)
			data->texture_pixels[i][j] = 0;
	}
}

void	display(t_data *data)
{
	reset_pixels(data);
	init_ray(&data->ray);
	raycasting(&data->player, data);
	display_frame(data);
}

int	render(t_data *data)
{
	data->player.has_moved += move(data);
	if (data->player.has_moved == 0)
		return (0);
	display(data);
	return (0);
}
