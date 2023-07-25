
#include "cub3d.h"

static void	draw_rectangle(t_data *data, t_img *img, t_rect *rect, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < rect->y_width)
	{
		x = 0;
		while (x < rect->x_width)
		{
			if (x + rect->x < data->win_width && y + rect->y < data->win_height)
				draw_pixel(img, x + rect->x, y + rect->y, color);
			x++;
		}
		y++;
	}
}

static int	check_minimap_wall(t_data *data, int x, int y)
{
	if ((int)data->player.pos_x + x >= data->max_x
		|| (int)data->player.pos_x + x < 0
		|| (int)data->player.pos_y + y >= data->max_y
		|| (int)data->player.pos_y + y < 0)
		return (0);
	if (data->map[(int)data->player.pos_y + y][(int)data->player.pos_x + x] == '1')
		return (1);
	return (0);
}

static void	draw_minimap_wall(t_data *data, t_mmap *mmap, int x, int y)
{
	t_rect	rect;

	rect.x = mmap->wall.x + mmap->wall.x_width * x;
	rect.x_width = mmap->wall.x_width;
	rect.y = mmap->wall.y + mmap->wall.y_width * y;
	rect.y_width = mmap->wall.y_width;
	if (rect.x < mmap->map.x)
	{
		rect.x_width -= mmap->map.x - rect.x;
		rect.x = mmap->map.x;
	}
	if (rect.y < mmap->map.y)
	{
		rect.y_width -= mmap->map.y - rect.y;
		rect.y = mmap->map.y;
	}
	draw_rectangle(data, mmap->img, &rect, 0x00ffffff);
}

static void	draw_minimap_info(t_data *data, t_mmap *mmap)
{
	int		step;
	int		x;
	int		y;

	mmap->player.x_width = mmap->map.x_width / 20;
	mmap->player.y_width = mmap->map.y_width / 20;
	mmap->player.y = mmap->map.y + mmap->map.y_width / 2 - mmap->player.y_width / 2;
	mmap->player.x = mmap->map.x + mmap->map.x_width / 2 - mmap->player.x_width / 2;
	draw_rectangle(data, mmap->img, &mmap->player, 0x00ff0000);
	mmap->wall.x_width = mmap->map.x_width / 10;
	mmap->wall.y_width = mmap->map.y_width / 10;
	mmap->wall.x = mmap->player.x - ((data->player.pos_x - (int)data->player.pos_x) * mmap->wall.x_width);
	mmap->wall.y = mmap->player.y - ((data->player.pos_y - (int)data->player.pos_y) * mmap->wall.y_width);
	step = -1;
	while ((++step - 1) * -1 * mmap->wall.x_width + mmap->wall.x > mmap->map.x
		|| (step - 1) * -1 * mmap->wall.y_width + mmap->wall.y > mmap->map.y)
	{
		x = -step - 1;
		while (++x <= step)
		{
			y = -step - 1;
			while (++y <= step)
				if (check_minimap_wall(data, x, y))
					draw_minimap_wall(data, mmap, x, y);
		}
	}
}

void	draw_minimap(t_data *data, t_img *img)
{
	t_mmap	mmap;

	mmap.map.y = data->win_height - data->win_height / 6;
	mmap.map.x = data->win_width - data->win_width / 6;
	mmap.map.y_width = data->win_height - mmap.map.y;
	mmap.map.x_width = data->win_width - mmap.map.x;
	mmap.img = img;
	draw_rectangle(data, img, &mmap.map, 0);
	draw_minimap_info(data, &mmap);
}