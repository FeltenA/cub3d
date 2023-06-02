
#include "libft.h"
#include "cub3d.h"

int	check_parse_map(char **map, t_data *data)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_isinlist(map[i][j], "0NSEW")
				&& (i == 0 || i == data->max_y || j == 0
				|| j == (int)ft_strlen(map[i])
				|| map[i - 1][j] == ' ' || map[i + 1][j] == ' '
				|| map[i][j - 1] == ' ' || map[i][j + 1] == ' '))
				return (0);
			if (ft_isinlist(map[i][j], "NSEW"))
				player++;
		}
	}
	if (player == 0 || player > 1)
		return (0);
	return (1);
}

int	check_parse_info(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEXT_NBR)
		if (!data->f_imgs[i].img.img || !data->f_imgs[i].img.addr)
			return (0);
	if (data->c_color == -1 || data->f_color == -1)
		return (0);
	return (1);
}
