#ifndef CUB3D_H
# define CUB3D_H


# include "../MLX/MLX42.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include "../parsing/cub.h"

# define SCALE 64
# define FOV 60
# define SPEED 200
# define ROTATE 4
# define W_WIDTH 900
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
    int 	  side_direction;
}    t_pos;

typedef struct s_img {
    mlx_image_t    *img;
}    t_img;

typedef struct s_texture {
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *east;
    mlx_texture_t *west;
} t_texture;

typedef struct s_map
{
	int map_h;
	int map_w;
    char       *n_textures;
    char       *s_textures;
    char       *e_textures;
    char       *w_textures;
    t_texture textures;
    char      **map;
    t_pos       p_pos;
    mlx_t      *mlx;
    t_img      img;
    t_data   *data;
} t_map;


void game_loop(void *param);
void key_hook(mlx_key_data_t keydata, void *param);
void move_player(t_map *map, float delta_time);
void draw_wall(t_map *map, int offset_x, int offset_y);
bool map_has_wall_at(t_map *map, double x, double y);
void my_mlx_pixel_put(t_img *data, int x, int y, uint32_t color);
t_pos get_best_intersection(t_map *map, double r_ang);
void load_textures(t_map *map);
void draw_ceiling(t_map *map, int column, int wall_top);
void draw_floor(t_map *map, int column, int wall_bottom);
void init_horizontal_intercept(double r_ang, float p_x, float p_y, float *y_intercept, float *x_intercept);
void calculate_horizontal_steps(double r_ang, float *y_step, float *x_step);
bool check_horizontal_wall(t_map *map, float next_x, float next_y, double r_ang);
float continue_horizontal_intersection(t_map *map, double r_ang, float p_x, float p_y, t_pos *horz_inter, float next_x, float next_y, float x_step, float y_step);
float find_horizontal_intersection(t_map *map, double r_ang, float p_x, float p_y,  t_pos *horz_inter);
void init_vertical_intercept(double r_ang, float p_x, float p_y,  float *x_intercept, float *y_intercept);
void calculate_vertical_steps(double r_ang, float *x_step, float *y_step);
bool check_vertical_wall(t_map *map, float next_x, float next_y, double r_ang);
float continue_vertical_intersection(t_map *map, double r_ang, float p_x, float p_y, t_pos *vert_inter, float next_x, float next_y, float x_step, float y_step);
float find_vertical_intersection(t_map *map, double r_ang, float p_x, float p_y,  t_pos *vert_inter);
void init_ray_casting(double *fov, int *num_rays, double *angle_increment);
void clear_screen(t_map *map);
double calculate_ray_angle(double player_angle, double fov, double angle_increment, int column);
void get_wall_hit_info(float horz_dist, float vert_dist, t_pos horz_inter, t_pos vert_inter, bool *is_horz_hit, t_pos *intersection,  double *distance);
void calculate_wall_dimensions(double distance, double ray_angle, double player_angle, double fov, int *wall_top, int *wall_bottom);
mlx_texture_t *select_texture(t_map *map, bool is_horz_hit, double ray_angle);
int calculate_texture_x(bool is_horz_hit, t_pos intersection, mlx_texture_t *texture);
void draw_wall_strip(t_map *map, int column, int wall_top, int wall_bottom, mlx_texture_t *texture, int tex_x);
double normalize_angle(double r_ang);

#endif
