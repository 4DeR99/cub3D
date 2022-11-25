/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:37:17 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/25 14:02:48 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>

#define BLOCK_SIZE 16
#define REAL_BLOCK_SIZE BLOCK_SIZE * 4
#define WALL_STRIP_WIDTH 2
#define FOV_ANGLE 60 * (M_PI / 180)
#define SIZEMINIMAP 2

/****_Key_hooks_***/
enum keys
{
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123,
	ESC = 53
};
/*----------------*/

/***************_MAP_****************/
typedef struct s_item
{
	char **map;
	int floor_colors[4];
	int ceiling_colors[4];
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int player_x;
	int player_y;
} t_item;
/*----------------------------------*/

/************_IMG_DATA-**************/
typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;
/*----------------------------------*/

/************_PLAYER_DATA************/
typedef struct s_p_data
{
	double rotation_angle;
	double x;
	double y;
	int turn_direction;
	double walk_angle;
	int walk_direction;
	double move_speed;
	double rotation_speed;
} t_p_data;
/*----------------------------------*/

/**************_RAYS_****************/
typedef struct s_ray
{
	double angle;
	double wallHitX;
	double wallHitY;
	double dst;
	int isFacingUp;
	int isFacingDown;
	int isFacingLeft;
	int isFacingRight;
} t_ray;
/*----------------------------------*/

/************_CUB3D_*****************/
typedef struct s_cub
{
	void *mlx;
	void *mlx_window;
	int win_width;
	int win_height;
	int num_rays;
	t_p_data *player;
	t_data *map_img;
	t_data *rend3D;
	t_ray *rays;
	t_item *map;
} t_cub;
/*----------------------------------*/

/**_LITERALLY CAUSE OF NORMINETTE_***/
typedef struct s_cords
{
	double x;
	double y;
} t_cords;

typedef struct s_m_cords
{
	double xinter;
	double yinter;
	double xstep;
	double ystep;
	double wallhitx;
	double wallhity;
	double dst;
} t_m_cords;
/*----------------------------------*/

/********************************_INIT_*********************************/
void cub_init(t_cub *cub);
void map_init(t_cub *cub);
void rend3R_init(t_cub *cub);
/*---------------------------------------------------------------------*/

/********************************_DRAW_*********************************/
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_line(t_cub *cub, double x2, double y2);
void draw_rect(t_cub *cub, t_cords cord1, t_cords cord2, double c);
/*---------------------------------------------------------------------*/

/*******************************_EVENTS_*******-************************/
int key_press(int keycode, t_cub *cub);
int key_release(int keycode, t_cub *cub);
void pos_update(t_cub *cub);
void angle_update(t_cub *cub);
/*---------------------------------------------------------------------*/

/*****************************_RAY_CASTING******************************/
int ray_cast(t_cub *cub, int ndx);
void upload_rays(t_cub *cub);
/*---------------------------------------------------------------------*/

/*********************************_MATH_********************************/
double mod(double n1, double n2);
double distance(double x1, double y1, double x2, double y2);
/*---------------------------------------------------------------------*/

/*********************************_MAP_*********************************/
int map_has_wall_at(t_cub *cub, double x, double y);
/*---------------------------------------------------------------------*/

/******************************_RENDERING_******************************/
void rend3r_walls(t_cub *cub, int ndx);
/*---------------------------------------------------------------------*/
/******************************_PARCING_********************************/
t_item *parser(void);
void map_parser(t_item *item);
int is_empty(char *str);
int is_line(char *str);
int is_wall(char *str);
int is_color(char *str);
// tools
char *ft_strchr(const char *s, int c);
size_t ft_strlen(const char *str);
int ft_atoi(const char *str);
char *ft_strdup(const char *s1);
char *ft_strjoin(char const *s1, char const *s2);
char **ft_split(char const *s, char c);
// free?
void free_map_items(t_item *item);
void free_str(char **tab);
/*---------------------------------------------------------------------*/

#endif