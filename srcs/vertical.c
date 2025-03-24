/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:49:47 by nal-haki          #+#    #+#             */
/*   Updated: 2025/03/25 01:07:00 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static float	calculate_delta_x(t_maindata *data, float *xvert,
					float *yvert, float angle)
{
	int		tx;
	float	remainder;
	bool	at_player;

	tx = (int)(*xvert / TILE_SIZE);
	at_player = (*xvert == data->player.player_x
			&& *yvert == data->player.player_y);
	if (angle > 90 && angle < 270)
	{
		if (at_player == false)
			return (TILE_SIZE);
		remainder = fmod(*xvert, TILE_SIZE);
		if (remainder == 0)
			return (TILE_SIZE);
		return (remainder);
	}
	if (at_player == false)
		return (-TILE_SIZE);
	return (*xvert - ((tx + 1) * TILE_SIZE));
}

static void	find_vertical_point(t_maindata *data, float rayangle,
					float *vertical_x, float *vertical_y)
{
	float	delta_x;
	float	tan_angle;

	if (rayangle == 90 || rayangle == 270)
		return ;
	delta_x = calculate_delta_x(data, vertical_x, vertical_y, rayangle);
	tan_angle = tan(radian(rayangle));
	*vertical_x -= delta_x;
	*vertical_y -= delta_x * tan_angle;
}

static bool	check_next_position(t_maindata *data, t_ray *ray, int *x, int *y)
{
	float	check_x;

	if (ray->rayangle == 90 || ray->rayangle == 270
		|| ray->vertical_x < 0 || ray->vertical_x > data->width_2d
		|| ray->vertical_y < 0 || ray->vertical_y > data->height_2d)
		return (true);
	check_x = ray->vertical_x;
	if (ray->vertical_x < data->player.player_x)
		check_x -= 1;
	*x = check_x / TILE_SIZE;
	*y = ray->vertical_y / TILE_SIZE;
	if (*y < 0 || *y >= data->map_height
		|| *x < 0 || *x >= (int)ft_strlen(data->map[*y]))
		return (true);
	return (data->map[*y][*x] == ' ');
}

void	vert_distance(t_maindata *data, t_ray *ray, float rayangle)
{
	int	x;
	int	y;

	ray->vertical_x = data->player.player_x;
	ray->vertical_y = data->player.player_y;
	ray->vert_distance = -1.0f;
	while (!check_next_position(data, ray, &x, &y))
	{
		if (data->map[y][x] == '1')
		{
			ray->vert_distance = get_distance(data,
					ray->vertical_x, ray->vertical_y);
			break ;
		}
		find_vertical_point(data, rayangle, &ray->vertical_x, &ray->vertical_y);
	}
}
