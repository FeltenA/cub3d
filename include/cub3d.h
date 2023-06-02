#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>

enum	e_textures {
	NO,
	SO,
	WE,
	EA
};

enum	e_values {
	TEXT_NBR = 4,
	RES_WIDTH = 800,
	RES_HEIGHT = 600
};

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_player
{
	t_pos	pos;
	double	angle;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_file_img
{
	t_img	img;
	int		width;
	int		heigth;
}	t_file_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	t_img		*img;
	char		**map;
	int			max_x;
	int			max_y;
	t_player	player;
	int			f_color;
	int			c_color;
	t_file_img	f_imgs[TEXT_NBR];
}	t_data;

void	free_data(t_data *data);
int		init_data(t_data *data);
int		is_empty_line(char *line);
int		check_each_char(char *str, int (*funct)(int c), int bool);
char	*remove_newline(char *line);
int		is_map_line(char *line);
int		print_error_parse(char *str);
int		check_parse_info(t_data *data);
int		check_parse_map(char **map, t_data *data);
int		parse_file(t_data *data, char *file);

#endif
