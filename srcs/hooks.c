/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:35:28 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/02 17:20:16 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	mlx_add_pixel(t_maindata *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return ;
	dst = data->img.addr + (y * data->img.length + x
			* (data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_maindata *data)
{
	free_memory(data->mlx, data->wall_textures);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	strings_free(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

static bool	check_keys(t_maindata *data)
{
	if (!data->keys[ROTATE_FLAG]
		&& !data->keys[MOVE_FLAG]
		&& !data->keys[CLOSE_FLAG])
		return (false);
	return (true);
}

int	loop_rendering(t_maindata *data)
{
	if (data->keys[CLOSE_FLAG])
		close_window(data);
	rotate(data);
	ft_moveplayer(data);
	if (!check_keys(data))
		return (0);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	data->keys[ROTATE_FLAG] = 0;
	data->keys[MOVE_FLAG] = 0;
	return (0);
}
