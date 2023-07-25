/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:12:15 by afelten           #+#    #+#             */
/*   Updated: 2023/05/31 17:12:17 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	print_error_parse(char *str)
{
	if (!write(2, "Error\n", 6))
		return (0);
	if (str)
		if (!write(2, str, ft_strlen(str)))
			return (0);
	return (0);
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

int	is_map_line(char *line)
{
	int	i;

	if (is_empty_line(line))
		return (0);
	i = -1;
	while (line[++i])
		if (!ft_isinlist(line[i], " 01NSEW"))
			return (0);
	return (1);
}
