#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>

# define MOVESPEED 0.0125
# define ROTSPEED 0.015

enum	e_keycodes {
	WKEY,
	AKEY,
	SKEY,
	DKEY,
	UPKEY,
	DOWNKEY,
	RIGHTKEY,
	LEFTKEY
};

enum	e_textures {
	NORTH,
	SOUTH,
	WEST,
	EAST
};

enum	e_values {
	TEX_NBR = 4,
	TEX_SIZE = 64,
	RES_WIDTH = 1200,
	RES_HEIGHT = 1000
};

typedef struct s_player
{
	char	chr;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_walldist;
	int		step_x;
	int		step_y;
	int		hit;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_tex
{
	int				size[TEX_NBR];
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_tex;

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
	int		height;
}	t_file_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	int			win_width;
	int			win_height;
	int			**texture_pixels;
	char		**map;
	int			max_x;
	int			max_y;
	t_ray		ray;
	t_player	player;
	int			f_color;
	int			c_color;
	t_tex		tex;
	t_file_img	f_imgs[TEX_NBR];
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int	x_width;
	int	y_width;
}	t_rect;

typedef struct s_mmap
{
	t_img	*img;
	t_rect	map;
	t_rect	player;
	t_rect	wall;
}	t_mmap;

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
void	init_player(t_player *player, int i, int j, char chr);

int		render(t_data *data);
int		close_window(t_data *data);
void	set_player_direction(t_player *player);
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);

void    draw_pixel(t_img *img, int x, int y, int color);
int		get_pixel(t_file_img *fimg, int x, int y);
void	draw_rectangle(t_data *data, t_img *img, t_rect *rect, int color);

#endif
