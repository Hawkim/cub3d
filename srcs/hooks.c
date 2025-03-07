/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by nal-haki          #+#    #+#             */
/*   Updated: 2024/12/19 13:54:43 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return ;
	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_win(t_data *data)
{
	free_textures_memory(data->mlx, data->wall_textures);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	strings_free(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

static bool	check_keys(t_data *data)
{
	if (!data->keys[ROTATE_FLAG]
		&& !data->keys[MOVE_FLAG]
		&& !data->keys[CLOSE_FLAG])
		return (false);
	return (true);
}

int	loop_rendering(t_data *data)
{
	if (data->keys[CLOSE_FLAG])
		close_win(data);
	rotate(data);
	move_player(data);
	if (!check_keys(data))
		return (0);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	data->keys[ROTATE_FLAG] = 0;
	data->keys[MOVE_FLAG] = 0;
	return (0);
}
