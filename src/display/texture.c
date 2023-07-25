/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:33 by mcombeau          #+#    #+#             */
/*   Updated: 2023/07/06 14:42:56 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_wall_index(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->tex.index = WEST;
		else
			data->tex.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->tex.index = SOUTH;
		else
			data->tex.index = NORTH;
	}
}

//on calcule la position x de la texture puis une boucle dans la direction
//y pour donner a chaque pixel de la bande verticale la coordonee de la
//texture texY qui est calcule en augmentant d'une taille de pas precalcule
//pour chaque pixel.
//
void	update_wall_pixels(t_data *data, t_tex *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	get_wall_index(data, ray);
	tex->x = (int)(ray->wall_x * (double)tex->size[tex->index]);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size[tex->index] - tex->x - 1;
	tex->step = 1.0 * tex->size[tex->index] / ray->line_height;
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size[tex->index] - 1);
		tex->pos += tex->step;
		color = get_pixel(&data->f_imgs[tex->index], tex->x, tex->y);
		if (color > 0)
			data->texture_pixels[y][x] = color;
		y++;
	}
}
