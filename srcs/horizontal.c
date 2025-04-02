/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:47:36 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/02 17:20:16 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	get_distance(t_maindata *data, float x, float y)
{
	return (sqrt(pow((data->player.player_x - x), 2)
			+ pow((data->player.player_y - y), 2)));
}

static float	calculate_delta_y(t_maindata *data, float *horiz_x
							, float *horiz_y, float rayangle)
{
	float	delta_y;

	if (rayangle > 180)
	{
		if (*horiz_x == data->player.player_x
			&& *horiz_y == data->player.player_y)
		{
			delta_y = *horiz_y
				- (((int)(*horiz_y / BLOCK_SIZE)) * (BLOCK_SIZE));
			if (delta_y == 0)
				delta_y = BLOCK_SIZE;
		}
		else
			delta_y = BLOCK_SIZE;
	}
	else
	{
		if (*horiz_x == data->player.player_x
			&& *horiz_y == data->player.player_y)
			delta_y = (*horiz_y)
				- (((int)((*horiz_y) / BLOCK_SIZE) + 1) * BLOCK_SIZE);
		else
			delta_y = -BLOCK_SIZE;
	}
	return (delta_y);
}

static void	find_horizontal_point(t_maindata *data, float rayangle
					, float *horiz_x, float *horiz_y)
{
	float	delta_x;
	float	delta_y;

	if (rayangle == 0 || rayangle == 180)
		return ;
	delta_y = calculate_delta_y(data, horiz_x, horiz_y, rayangle);
	delta_x = delta_y / tan(radian(rayangle));
	*horiz_x = *horiz_x - delta_x;
	*horiz_y = *horiz_y - delta_y;
}

static bool	check_next_position(t_maindata *data, t_ray *ray, int *x, int *y)
{
	float	check_y;

	if (ray->rayangle == 0 || ray->rayangle == 180
		|| ray->horiz_y > data->height_2d || ray->horiz_y < 0
		|| ray->horiz_x > data->width_2d || ray->horiz_x < 0)
		return (true);
	check_y = ray->horiz_y;
	if (ray->horiz_y < data->player.player_y)
		check_y -= 1;
	*x = ray->horiz_x / BLOCK_SIZE;
	*y = check_y / BLOCK_SIZE;
	if ((*y < data->map_height && *y >= 0) && (*x >= 0
			&& *x < (int)ft_strlen(data->map[*y])))
	{
		if (data->map[*y][*x] == ' ')
			return (true);
	}
	else
		return (true);
	return (false);
}

void	horiz_distance(t_maindata *data, t_ray *ray, float rayangle)
{
	int		x;
	int		y;

	ray->horiz_y = data->player.player_y;
	ray->horiz_x = data->player.player_x;
	ray->horiz_distance = -1.0;
	while (1)
	{
		find_horizontal_point(data, rayangle, &ray->horiz_x,
			&ray->horiz_y);
		if (check_next_position(data, ray, &x, &y))
			break ;
		if (data->map[y][x] == '1')
		{
			ray->horiz_distance = get_distance(data, ray->horiz_x,
					ray->horiz_y);
			break ;
		}
	}
}
