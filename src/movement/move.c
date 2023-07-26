/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:01:30 by qrolland          #+#    #+#             */
/*   Updated: 2023/07/24 16:01:31 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	move_forward(t_data *data)
{
	double	x;
	double	y;

	x = data->player.pos_x + data->player.dir_x * MOVESPEED;
	y = data->player.pos_y + data->player.dir_y * MOVESPEED;
	return (position(data, x, y));
}

static int	move_backward(t_data *data)
{
	double	x;
	double	y;

	x = data->player.pos_x - data->player.dir_x * MOVESPEED;
	y = data->player.pos_y - data->player.dir_y * MOVESPEED;
	return (position(data, x, y));
}

static int	move_left(t_data *data)
{
	double	x;
	double	y;

	x = data->player.pos_x + data->player.dir_y * MOVESPEED;
	y = data->player.pos_y - data->player.dir_x * MOVESPEED;
	return (position(data, x, y));
}

static int	move_right(t_data *data)
{
	double	x;
	double	y;

	x = data->player.pos_x - data->player.dir_y * MOVESPEED;
	y = data->player.pos_y + data->player.dir_x * MOVESPEED;
	return (position(data, x, y));
}

int	move(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->player.move_y == 1)
		moved += move_forward(data);
	if (data->player.move_y == -1)
		moved += move_backward(data);
	if (data->player.move_x == -1)
		moved += move_left(data);
	if (data->player.move_x == 1)
		moved += move_right(data);
	if (data->player.rotate != 0)
		moved += rotation(data, data->player.rotate);
	return (moved);
}
