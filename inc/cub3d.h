#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../gl/get_next_line.h"
# include "../MLX/MLX42.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>


# define SCALE 64
# define FOV 60
# define SPEED 100
# define ROTATE 4
# define W_WIDTH 1200
# define W_HEIGHT 900

typedef struct s_vars {
    mlx_t          *mlx;
    mlx_t   *win;
}    t_vars;

typedef struct s_pos
{
    double    x;
    double    y;
	double    ang;
	int 	  walk_direction;
	int 	  rotate_direction;
}    t_pos;

typedef struct s_data {
    mlx_image_t    *img;
}    t_data;

typedef struct s_map
{
	int map_h;
	int map_w;
    int         checker;
    char       *n_textures;
    char       *s_textures;
    char       *e_textures;
    char       *w_textures;
    int         f_col;
    int         c_col;
    char      **map;
    t_pos       p_pos;
    mlx_t      *mlx;
    t_data      img;
} t_map;


void game_loop(void *param);
void key_hook(mlx_key_data_t keydata, void *param);
void draw_image(void *param);
void draw_player(t_map *map);
void move_player(t_map *map, float delta_time);
void draw_map(t_map *map);
void draw_wall(t_map *map, int offset_x, int offset_y);
bool map_has_wall_at(t_map *map, double x, double y);
void my_mlx_pixel_put(t_data *data, int x, int y, uint32_t color);
void DDA(t_pos p_pos, t_pos inter_pos, t_map *map);
t_pos get_best_intersection(t_map *map, double r_ang);
float find_horizontal_intersection(t_map *map, double r_ang, float p_x, float p_y, t_pos *horz_inter);
float find_vertical_intersection(t_map *map, double r_ang, float p_x, float p_y, t_pos *vert_inter);
int abs(int n);


#endif
