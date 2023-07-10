
#include "cub3d.h"
#include "libft.h"
#include <math.h>

static int	fill_map(t_data *data, int fd, char **line)
{
	int		i;
	char	**save;

	i = 0;
	while (*line && is_map_line(*line))
	{
		save = ft_realloc(data->map, i * sizeof(char *),
				(i + 2) * sizeof(char *));
		if (!save)
			return (0);
		data->map = save;
		data->map[i] = *line;
		data->map[i + 1] = 0;
		i++;
		if (data->max_x < (int)ft_strlen(*line))
			data->max_x = ft_strlen(*line);
		*line = remove_newline(get_next_line(fd));
	}
	return (1);
}

static int	format_map(t_data *data)
{
	int		i;
	int		j;
	int		len;
	char	*save;

	i = -1;
	while (data->map[++i])
	{
		len = ft_strlen(data->map[i]);
		if (len < data->max_x)
		{
			save = ft_realloc(data->map[i], len, data->max_x);
			if (!save)
				return (print_error_parse("Map formatting failed\n"));
			data->map[i] = save;
			j = len - 1;
			while (++j < data->max_x)
				data->map[i][j] = ' ';
			data->map[i][j] = 0;
		}
	}
	return (1);
}

static int	get_map(t_data *data, int fd, char *line)
{
	while (line && !is_map_line(line))
	{
		free(line);
		line = remove_newline(get_next_line(fd));
	}
	if (!line)
		return (0);
	if (!fill_map(data, fd, &line))
		return (0);
	if (line && !is_map_line(line))
		free(line);
	data->max_y = ft_array_len((void **)data->map);
	return (1);
}

static void	get_player_values(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (ft_isinlist(data->map[i][j], "NSEW"))
			{
				init_player(&data->player, i, j, data->map[i][j]);
				return ;
			}
		}
	}
}

int	parse_map(t_data *data, int fd, char *line)
{
	if (!get_map(data, fd, line) || check_parse_map(data->map, data))
		return (print_error_parse("Map not valid\n"));
	get_player_values(data);
	return (format_map(data));
}
