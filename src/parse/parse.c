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

int	parse_map(t_data *data, int fd, char *line);

static void	parse_texture(t_data *data, int index, char **info)
{
	t_file_img	*f_img;

	f_img = &data->f_imgs[index];
	f_img->img.img = mlx_xpm_file_to_image(data->mlx, info[1],
			&f_img->width, &f_img->height);
	if (!f_img->img.img)
		return ;
	f_img->img.addr = mlx_get_data_addr(f_img->img.img, &f_img->img.bpp,
			&f_img->img.line_len, &f_img->img.endian);
}

static void	parse_color(t_data *data, char **info)
{
	char			**colors;
	int				len;
	unsigned char	rgb[4];

	colors = ft_split(info[1], ',');
	if (!colors)
		return ;
	len = ft_array_len((void **)colors);
	if (len != 3 || ft_strlen(colors[0]) > 3
		|| ft_strlen(colors[1]) > 3 || ft_strlen(colors[2]) > 3
		|| check_each_char(colors[0], &ft_isdigit, 0)
		|| check_each_char(colors[1], &ft_isdigit, 0)
		|| check_each_char(colors[2], &ft_isdigit, 0)
		|| ft_atoi(colors[2]) > 255 || ft_atoi(colors[1]) > 255
		|| ft_atoi(colors[0]) > 255)
		return (ft_array_free((void **)colors, len, &free));
	rgb[0] = ft_atoi(colors[2]);
	rgb[1] = ft_atoi(colors[1]);
	rgb[2] = ft_atoi(colors[0]);
	rgb[3] = 0;
	if (!ft_strcmp(info[0], "F"))
		data->f_color = *((int *)rgb);
	else if (!ft_strcmp(info[0], "C"))
		data->c_color = *((int *)rgb);
	ft_array_free((void **)colors, len, &free);
}

static void	choose_text(t_data *data, char **info)
{
	if (!info || !info[0] || !info[1])
		return ;
	if (!ft_strcmp(info[0], "F") || !ft_strcmp(info[0], "C"))
		parse_color(data, info);
	else if (!ft_strcmp(info[0], "NO"))
		parse_texture(data, NORTH, info);
	else if (!ft_strcmp(info[0], "SO"))
		parse_texture(data, SOUTH, info);
	else if (!ft_strcmp(info[0], "WE"))
		parse_texture(data, WEST, info);
	else if (!ft_strcmp(info[0], "EA"))
		parse_texture(data, EAST, info);
}

static char	*parse_info(t_data *data, int fd)
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

int	parse_file(t_data *data, char *file)
{
	int		save;
	int		fd;
	char	*line;

	if (ft_strlen(file) < 4 || ft_strcmp(file + ft_strlen(file) - 4, ".cub"))
		return (print_error_parse("Map file is not valid\n"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error_parse("Cannot open map file\n"));
	line = parse_info(data, fd);
	if (!line && !check_parse_info(data))
	{
		close(fd);
		return (print_error_parse("Map info not valid\n"));
	}
	save = parse_map(data, fd, line);
	close(fd);
	return (save);
}
