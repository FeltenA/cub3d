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
	TEXT_NBR = 4
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
	char	c;
	t_img	img;
	int		width;
	int		heigth;
}	t_file_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		*img;
	char		**map;
	int			max_x;
	int			max_y;
	int			f_color;
	int			c_color;
	t_file_img	f_imgs[TEXT_NBR];
}	t_data;

#endif