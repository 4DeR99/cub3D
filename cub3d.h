/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:37:17 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/15 15:01:53 by moulmado         ###   ########.fr       */
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

#define BLOCK_SIZE 16
#define REAL_BLOCK_SIZE BLOCK_SIZE
#define WALL_STRIP_WIDTH 0.1
#define FOV_ANGLE 60 * (M_PI / 180)

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

// typedef struct s_map
// {
// 	// int grid[11][15];
// 	t_data *wall;
// 	t_data *empty;
// } t_map;

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
	t_p_data *player;
	t_data *map;
	t_data *rend3D;
	t_ray *rays;
} t_cub;

/*********************_LITTERALY CAUSE FOF NORMINETTE*******************/
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
/*---------------------------------------------------------------------*/

/********************************_INIT_*********************************/
void cub_init(t_cub *cub);
/*---------------------------------------------------------------------*/

/********************************_DRAW_*********************************/
void map_init(t_cub *cub);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_line(t_cub *cub, double x2, double y2);
void draw_rect(t_cub *cub, t_cords cord1, t_cords cord2);
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
void rend3R_init(t_cub *cub);
void rend3r_walls(t_cub *cub, int ndx);
/*---------------------------------------------------------------------*/

#endif