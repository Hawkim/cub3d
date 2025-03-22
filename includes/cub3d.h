/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:03:31 by nal-haki          #+#    #+#             */
/*   Updated: 2025/03/06 14:55:28 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>

# define TILE_SIZE 1000         // Size of each tile in the map (used for scaling).
# define MIN_TILE_SIZE 10       // Minimum size of a tile (used for scaling or constraints).
# define WIDTH 1080             // Width of the game window in pixels.
# define HEIGHT 720             // Height of the game window in pixels.

# define W 119                  //  for the 'W' key (move forward).
# define A 97                   //  for the 'A' key (move left).
# define S 115                  //  for the 'S' key (move backward).
# define D 100                  //  for the 'D' key (move right).
# define RIGHT 65363            //  for the right arrow key (rotate right).
# define LEFT 65361             //  for the left arrow key (rotate left).
# define UP 65362               //  for the up arrow key (unused).
# define DOWN 65364             //  for the down arrow key (unused ).
# define CLOSE 65307            //  for the 'Esc' key (close the game).

# define IMG_SIZE_X 4           // Width of texture images 
# define IMG_SIZE_Y 4           // Height of texture images 

# define ANGLE 1.5              // Angle increment for player rotation (in degrees).
# define WALL_COLOR 0x61F5B5    // Color for rendering walls (in hexadecimal).
# define DIR_COLOR 0xFF0000     // Color for rendering the player's direction (red).
# define BLACK 0x000000         // Color for rendering black (used for background or empty space).

# define FOV 60                 // Field of View (angle in degrees visible to the player).
# define SPEED_DIVISOR 10 		// Divisor for player movement  (controls how fast the player moves).

# define N_INDEX 0              // Index for the north wall texture.
# define S_INDEX 1              // Index for the south wall texture.
# define W_INDEX 2              // Index for the west wall texture.
# define E_INDEX 3              // Index for the east wall texture.

# define RIGHT_FLAG 0           // Flag for right arrow key (rotate right).
# define LEFT_FLAG 1            // Flag for left arrow key (rotate left).
# define W_FLAG 2               // Flag for 'W' key (move forward).
# define S_FLAG 3               // Flag for 'S' key (move backward).
# define D_FLAG 4               // Flag for 'D' key (move right).
# define A_FLAG 5               // Flag for 'A' key (move left).
# define CLOSE_FLAG 6           // Flag for 'Esc' key (close the game).
# define ROTATE_FLAG 7          // Flag for rotation actions (combined rotation logic).
# define MOVE_FLAG 8            // Flag for movement actions (combined movement logic).
# define KEYS_NB 9              // Total number of key flags (used for array sizing).

typedef struct s_texture
{
	void	*img;
	char	*iter;
	int		line_length;
	int		pixel_bits;
	int		endianess;
	int		width;
	int		height;
}	t_texture;

typedef struct s_ray
{
	float	colums;
	float	distance;
	float	rayangle;
	float	raystep;
	float	horiz_x;
	float	horiz_y;
	float	horiz_distance;
	float	vertical_x;
	float	vertical_y;
	float	vert_distance;
	int		side_flag;
	int		curr_color;
	int		texture_idx;
	float	height;
}	t_ray;

typedef struct s_player
{
	float	player_x;
	float	player_y;
	float	angle;
	float	fov;
	float	angle_step;
	float	distance_to_project_plan;
	float	first_x_fov;
	float	last_x_fov;
	float	first_y_fov;
	float	last_y_fov;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_maindata
{
	int			map_height;
	int			map_width;
	char		**map;
	void		*mlx;
	void		*win;
	int			width_2d;
	int			height_2d;
	t_img		img;
	t_player	player;
	t_texture	wall_textures[4];
	int			ceiling_color;
	int			floor_color;
	bool		keys[KEYS_NB];
}	t_maindata;

void	free_memory(void *mlx, t_texture *my_textures);
void	get_start(t_config *parsed_data);
void	intitialize_keyflags(t_maindata *data);
int		ft_press_key(int key, t_maindata *data);
int		ft_release_key(int key, t_maindata *data);
int		loop_rendering(t_maindata *data);
int		close_window(t_maindata *data);
void	mlx_add_pixel(t_maindata *data, int x, int y, int color);
float	radian(float degree);
void	rotate(t_maindata *data);
void	ft_moveplayer(t_maindata *data);
void	raycasting(t_maindata *data);
void	draw(t_maindata *data);
void	horiz_distance(t_maindata *data, t_ray *ray, float rayangle);
float	get_distance(t_maindata *data, float x, float y);
void	vert_distance(t_maindata *data, t_ray *ray, float rayangle);
void	get_texture_color(t_maindata *data, t_ray *ray, int current_y);
void	initialize_textures(t_maindata *data, t_config *parsed_data);
bool	check_barriers(t_maindata *data, float x, float y);
#endif