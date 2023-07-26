
#include "cub3d.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	if (x < 0 || y < 0 || 4 * x >= img->line_len)
		return ;
	*(int *)(img->addr + img->line_len * y + 4 * x) = color;
}

int	get_pixel(t_file_img *fimg, int x, int y)
{
	if (x < 0 || y < 0 || x >= fimg->width || y >= fimg->height)
		return (-1);
	return (*(int *)(fimg->img.addr + fimg->img.line_len * y + 4 * x));
}

void	draw_rectangle(t_data *data, t_img *img, t_rect *rect, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < rect->y_width)
	{
		x = 0;
		while (x < rect->x_width)
		{
			if (x + rect->x < data->win_width
				&& y + rect->y < data->win_height)
				draw_pixel(img, x + rect->x, y + rect->y, color);
			x++;
		}
		y++;
	}
}
