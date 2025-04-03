/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:45 by nal-haki          #+#    #+#             */
/*   Updated: 2025/03/26 22:41:33 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	player_initial_xy(t_maindata *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->player.player_x = (x * BLOCK_SIZE + BLOCK_SIZE / 2);
				data->player.player_y = (y * BLOCK_SIZE + BLOCK_SIZE / 2);
				return ;
			}
		}
	}
}

static void	initialsetup(t_maindata *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return ;
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&(data->img.bits_per_pixel), &(data->img.length),
			&(data->img.endian));
	data->width_2d = (data->map_width * BLOCK_SIZE);
	data->height_2d = (data->map_height * BLOCK_SIZE);
	player_initial_xy(data);
	data->player.fov = FOV;
	data->player.projection_plane_dist = ((float)WIDTH / 2)
		/ tan(radian(data->player.fov / 2));
}

static void	first_view(t_maindata *data)
{
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	start(t_config *parsed_data)
{
	t_maindata	data;

	if (!parsed_data || !parsed_data->map)
		return ;
	data.map = parsed_data->map;
	data.ceiling_color = parsed_data->ceiling_color;
	data.floor_color = parsed_data->floor_color;
	data.map_height = parsed_data->map_height;
	data.map_width = parsed_data->map_width;
	data.player.angle = parsed_data->player_start_angle;
	data.player.angle_step = ((float)FOV / (float)WIDTH);
	initialsetup(&data);
	initialize_textures(&data, parsed_data);
	parsed_data->map = NULL;
	free_parsed_data(parsed_data);
	initialize_keys(&data);
	first_view(&data);
	mlx_hook(data.win, 17, 1L << 2, close_window, &data);
	mlx_hook(data.win, 2, 1L << 0, ft_press_key, &data);
	mlx_hook(data.win, 3, 1L << 1, ft_release_key, &data);
	mlx_loop_hook(data.mlx, loop_rendering, &data);
	mlx_loop(data.mlx);
}
