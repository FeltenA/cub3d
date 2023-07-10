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

typedef struct s_rect
{
	int	x;
	int	y;
	int	x_width;
	int	y_width;
}	t_rect;

void	draw_rectangle(t_data *data, t_img *img, t_rect *rect, char color)
{
	int	x;
	int	y;

	y = rect->y;
	while (y < rect->y_width)
	{
		x = rect->x;
		while (x < rect->x_width)
		{
			img->addr[y * data->win_width + x] = color;
			x++;
		}
		y++;
	}
}

void	draw_minimap_info(t_data *data, t_img *img, t_rect *map)
{
	t_rect	rect;

	rect.y = map->y + map->y_width / 2;
	rect.x = map->x + map->x_width / 2;
	rect.x_width = map->x_width / 10;
	rect.y_width = map->y_width / 10;
	draw_rectangle(data, img, &rect, 0xff0000);
}

void	draw_minimap(t_data *data, t_img *img)
{
	t_rect	rect;

	rect.y = data->win_height - data->win_height / 10;
	rect.x = data->win_width - data->win_width / 10;
	rect.y_width = data->win_height - rect.y;
	rect.x_width = data->win_width - rect.x;
	draw_rectangle(data, img, &rect, 0);
	draw_minimap_info(data, img, &rect);
}

static void	set_frame_pixel(t_data *data, t_img *image, int x, int y)
{
	int	pixel;

	pixel = x + y * (image->line_len / 4);
	if (data->texture_pixels[y][x] > 0)
		image->addr[pixel] = data->texture_pixels[y][x];
	else if (y < data->win_height / 2)
		image->addr[pixel] = data->c_color;
	else if (y < data->win_height - 1)
		image->addr[pixel] = data->f_color;
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

int	render(t_data *data)
{
	create_texture_pixels(data);
	init_ray(&data->ray);
	raycasting(&data->player, data);
	display_frame(data);
	return (0);
}
