/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:37:17 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/13 17:49:55 by moulmado         ###   ########.fr       */
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

#define BLOCK_SIZE 32
#define WALL_STRIP_WIDTH 1
#define FOV_ANGLE 60 * (M_PI / 180)
#define MAP_SCALE_FACTOR 0.2

/*    Key_hooks   */
#define W 13
#define A 0
#define S 1
#define D 2
#define UP 126
#define DOWN 125
#define RIGHT 124
#define LEFT 123
#define ESC 53
/*----------------*/

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_map
{
	// int grid[11][15];
	t_data *wall;
	t_data *empty;
} t_map;

typedef struct s_p_data
{
	t_data *dot;
	double rotation_angle;
	double x;
	double y;
	int turn_direction;
	double walk_angle;
	int walk_direction;
	double move_speed;
	double rotation_speed;
} t_p_data;

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

typedef struct s_cub
{
	void *mlx;
	void *mlx_window;
	int win_width;
	int win_heigh;
	int num_rays;
	t_data *ray_2_put;
	t_p_data *player;
	t_map *map;
	t_ray *rays;
} t_cub;

/*********************_LITTERALY CAUSE FOF NORMINETTE*******************/
typedef struct s_cords
{
	double xinter;
	double yinter;
	double xstep;
	double ystep;
	double wallhitx;
	double wallhity;
	double dst;
} t_cords;
/*---------------------------------------------------------------------*/

/********************************_INIT_*********************************/
void cub_init(t_cub *mycub);
/*---------------------------------------------------------------------*/

/********************************_DRAW_*********************************/
void draw_map(t_cub *mycub);
void draw_player(t_cub *mycub);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_line(t_cub *mycub, double x2, double y2);
/*---------------------------------------------------------------------*/

/*******************************_EVENTS_*******-************************/
int key_press(int keycode, t_cub *mycub);
int key_release(int keycode, t_cub *mycub);
void pos_update(t_cub *mycub);
void angle_update(t_cub *mycub);
/*---------------------------------------------------------------------*/

/*****************************_RAY_CASTING******************************/
void ray_cast(t_cub *mycub, int ndx);
void upload_rays(t_cub *mycub);
/*---------------------------------------------------------------------*/

/*********************************_MATH_********************************/
double mod(double n1, double n2);
double dst_between_points(double x1, double y1, double x2, double y2);
/*---------------------------------------------------------------------*/

/*********************************_MAP_*********************************/
int map_has_wall_at(t_cub *mycub, double x, double y);
/*---------------------------------------------------------------------*/

#endif