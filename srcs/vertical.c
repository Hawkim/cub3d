/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:49:47 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/02 17:20:16 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static float	calculate_delta_x(t_maindata *data, float *xvert,
					float *yvert, float angle)
{
	int		tx;
	float	remainder;
	bool	at_player;

	tx = (int)(*xvert / BLOCK_SIZE);
	at_player = (*xvert == data->player.player_x
			&& *yvert == data->player.player_y);
	if (angle > 90 && angle < 270)
	{
		if (at_player == false)
			return (BLOCK_SIZE);
		remainder = fmod(*xvert, BLOCK_SIZE);
		if (remainder == 0)
			return (BLOCK_SIZE);
		return (remainder);
	}
	if (at_player == false)
		return (-BLOCK_SIZE);
	return (*xvert - ((tx + 1) * BLOCK_SIZE));
}

static void	find_vertical_point(t_maindata *data, float rayangle,
					float *vert_x, float *vert_y)
{
	float	delta_x;
	float	tan_angle;

	if (rayangle == 90 || rayangle == 270)
		return ;
	delta_x = calculate_delta_x(data, vert_x, vert_y, rayangle);
	tan_angle = tan(radian(rayangle));
	*vert_x -= delta_x;
	*vert_y -= delta_x * tan_angle;
}

static bool	check_next_position(t_maindata *data, t_ray *ray, int *x, int *y)
{
	float	check_x;

	if (ray->rayangle == 90 || ray->rayangle == 270
		|| ray->vert_x < 0 || ray->vert_x > data->width_2d
		|| ray->vert_y < 0 || ray->vert_y > data->height_2d)
		return (true);
	check_x = ray->vert_x;
	if (ray->vert_x < data->player.player_x)
		check_x -= 1;
	*x = check_x / BLOCK_SIZE;
	*y = ray->vert_y / BLOCK_SIZE;
	if (*y < 0 || *y >= data->map_height
		|| *x < 0 || *x >= (int)ft_strlen(data->map[*y]))
		return (true);
	return (data->map[*y][*x] == ' ');
}

void	vert_distance(t_maindata *data, t_ray *ray, float rayangle)
{
	int	x;
	int	y;

	ray->vert_x = data->player.player_x;
	ray->vert_y = data->player.player_y;
	ray->vert_distance = -1.0f;
	while (!check_next_position(data, ray, &x, &y))
	{
		if (data->map[y][x] == '1')
		{
			ray->vert_distance = get_distance(data,
					ray->vert_x, ray->vert_y);
			break ;
		}
		find_vertical_point(data, rayangle, &ray->vert_x, &ray->vert_y);
	}
}
