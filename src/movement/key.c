/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:26:09 by qrolland          #+#    #+#             */
/*   Updated: 2023/07/24 16:01:35 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == 0xff1b)
		close_window(data);
	if (key == 0xff51)
		data->player.rotate -= 1;
	if (key == 0xff53)
		data->player.rotate += 1;
	if (key == 0x0077)
		data->player.move_y = 1;
	if (key == 0x0061)
		data->player.move_x = -1;
	if (key == 0x0073)
		data->player.move_y = -1;
	if (key == 0x0064)
		data->player.move_x = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 0xff1b)
		close_window(data);
	if (key == 0x0077 && data->player.move_y == 1)
		data->player.move_y = 0;
	if (key == 0x0073 && data->player.move_y == -1)
		data->player.move_y = 0;
	if (key == 0x0061 && data->player.move_x == -1)
		data->player.move_x += 1;
	if (key == 0x0064 && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (key == 0xff51 && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (key == 0xff53 && data->player.rotate >= -1)
		data->player.rotate = 0;
	return (0);
}
