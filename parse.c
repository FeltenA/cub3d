/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:11:41 by afelten           #+#    #+#             */
/*   Updated: 2023/05/31 17:11:44 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

int	print_error_parse(char *str)
{
	write(2, "Error\n", 6);
	if (str)
		write(2, str, ft_strlen(str));
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (i < TEXT_NBR)
		if (data->f_imgs[i].img.img)
			mlx_destroy_image(data->mlx, data->f_imgs[i].img.img);
	if (data->map)
		ft_array_free((void **)data->map,
			ft_array_len((void **)data->map), &free);
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		free(data->img);
	}
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	init_data(t_data *data)
{
	int	i;

	data->mlx = 0;
	data->mlx_win = 0;
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
		if (i <= EA)
			data->f_imgs[i].c = '1';
	}
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

int	is_empty_line(char *line)
{
	while (*line && *line != '\n')
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

void	parse_texture(t_data *data, int index, char **info)
{
	t_file_img	*f_img;

	f_img = &data->f_imgs[index];
	f_img->img.img = mlx_xpm_file_to_image(data->mlx, info[1],
			&f_img->width, &f_img->heigth);
	if (!f_img->img.img)
		return ;
	f_img->img.addr = mlx_get_data_addr(f_img->img.img, &f_img->img.bpp,
			&f_img->img.line_len, &f_img->img.endian);
}

int	check_each_char(char *str, int (*funct)(int c), int bool)
{
	while (*str)
	{
		if (bool && (*funct)(*str))
			return (1);
		else if (!bool && !(*funct)(*str))
			return (1);
		str++;
	}
	return (0);
}

void	parse_color(t_data *data, char **info)
{
	char			**colors;
	int				len;
	unsigned char	rgb[4];

	colors = ft_split(info[1], ',');
	if (!colors)
		return ;
	len = ft_array_len((void **)colors);
	if (len != 3 || (ft_strlen(colors[0]) < 4
			&& ft_strlen(colors[1]) < 4 && ft_strlen(colors[2]) < 4))
		return (ft_array_free((void **)colors, len, &free));
	if (check_each_char(colors[0], &ft_isdigit, 0)
		|| check_each_char(colors[1], &ft_isdigit, 0)
		|| check_each_char(colors[2], &ft_isdigit, 0))
		return (ft_array_free((void **)colors, len, &free));
	rgb[0] = ft_atoi(colors[2]);
	rgb[1] = ft_atoi(colors[1]);
	rgb[2] = ft_atoi(colors[0]);
	rgb[3] = 0;
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (ft_array_free((void **)colors, len, &free));
	if (!ft_strcmp(info[0], "F"))
		data->f_color = *(int *)rgb;
	else if (!ft_strcmp(info[0], "C"))
		data->c_color = *(int *)rgb;
	ft_array_free((void **)colors, len, &free);
}

void	choose_text(t_data *data, char **info)
{
	if (!info || !info[0] || !info[1])
		return ;
	if (!ft_strcmp(info[0], "F") || !ft_strcmp(info[0], "C"))
		parse_color(data, info);
	else if (!ft_strcmp(info[0], "NO"))
		parse_texture(data, NO, info);
	else if (!ft_strcmp(info[0], "SO"))
		parse_texture(data, SO, info);
	else if (!ft_strcmp(info[0], "WE"))
		parse_texture(data, WE, info);
	else if (!ft_strcmp(info[0], "EA"))
		parse_texture(data, EA, info);
}

char	*remove_newline(char *line)
{
	int	i;

	if (!line)
		return (line);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[i] = 0;
	return (line);
}

char	*parse_info(t_data *data, int fd)
{
	char	*line;
	char	**info;

	line = remove_newline(get_next_line(fd));
	while (line && !check_parse_info(data))
	{
		if (!is_empty_line(line))
		{
			info = ft_split_funct(line, &ft_isspace);
			if (!info)
			{
				free(line);
				return (0);
			}
			choose_text(data, info);
			ft_array_free((void **)info, ft_array_len((void **)info), &free);
		}
		free(line);
		line = remove_newline(get_next_line(fd));
	}
	return (line);
}

int	is_map_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isinlist(line[i], " 01NSEW"))
			return (0);
	return (1);
}

int	parse_map(t_data *data, int fd, char *line)
{
	int		i;
	char	**save;

	while (line && !is_map_line(line))
	{
		free(line);
		line = remove_newline(get_next_line(fd));
	}
	if (!line)
		return (0);
	i = 0;
	while (line && is_map_line(line))
	{
		save = ft_realloc(data->map, i * sizeof(char *), (i + 2) * sizeof(char *));
		if (!save)
			return (0);
		data->map = save;
		data->map[i] = line;
		data->map[i + 1] = 0;
		if (data->max_x < (int)ft_strlen(line))
			data->max_x = ft_strlen(line);
		line = remove_newline(get_next_line(fd));
	}
	if (line && !is_map_line(line))
		free(line);
	data->max_y = ft_array_len((void **)data->map);
	return (1);
}

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
				&& (i == 0 || i == data->max_y || j == 0 || j == (int)ft_strlen(map[i])
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

int	format_map(t_data *data)
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
				return (print_error_parse("Map formatting failed"));
			data->map[i] = save;
			j = len - 1;
			while (++j < data->max_x)
				data->map[i][j] = ' ';
			data->map[i][j] = 0;
		}
	}
	return (1);
}

int	parse_file(t_data *data, char *file)
{
	int		save;
	int		fd;
	char	*line;

	if (ft_strlen(file) < 4 || ft_strcmp(file + ft_strlen(file) - 4, ".cub"))
		return (print_error_parse("Map file is not valid"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error_parse("Cannot open map file"));
	line = parse_info(data, fd);
	if (!line && !check_parse_info(data))
	{
		close(fd);
		return (print_error_parse("Map info not valid"));
	}
	save = !parse_map(data, fd, line);
	close(fd);
	if (save || !check_parse_map(data->map, data))
		return (print_error_parse("Map not valid"));
	return (format_map(data));
}
