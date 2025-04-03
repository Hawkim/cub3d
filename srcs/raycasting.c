/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/29 17:33:03 by nal-haki          #+#    #+#             */
/*   Updated: 2025/03/06 13:29:35 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	height_and_texture(t_maindata *data, t_ray *ray)
{
	if (ray->side_flag == 1)
	{
		if (ray->rayangle >= 180)
			ray->texture_index = NORTH_INDEX;
		else
			ray->texture_index = SOUTH_INDEX;
	}
	else
	{
		if ((ray->rayangle >= 0 && ray->rayangle <= 90)
			|| ray->rayangle >= 270)
			ray->texture_index = EAST_INDEX;
		else
			ray->texture_index = WEST_INDEX;
	}
	ray->height = ((float)BLOCK_SIZE / ray->distance)
		* data->player.projection_plane_dist;
}

static void	draw_column(t_maindata *data, t_ray *ray, int column)
{
	int	start;
	int	end;
	int	i;

	height_and_texture(data, ray);
	start = (HEIGHT - ray->height) / 2;
	end = start + ray->height;
	if (end > HEIGHT)
		end = HEIGHT;
	i = -1;
	while (++i < start)
		mlx_add_pixel(data, column, i, data->ceiling_color);
	i = -1;
	if (start > 0)
		i = start - 1;
	while (++i < end)
	{
		get_texture_color(data, ray, i - start);
		mlx_add_pixel(data, column, i, ray->pixel_color);
	}
	while (i < HEIGHT)
		mlx_add_pixel(data, column, i++, data->floor_color);
}

static void	real_distance(t_ray *ray, t_maindata *data)
{
	if (ray->horiz_distance != -1)
		ray->horiz_distance = cos(radian(ray->rayangle
					- data->player.angle)) * ray->horiz_distance;
	if (ray->vert_distance != -1)
		ray->vert_distance = cos(radian(ray->rayangle - data->player.angle))
			* ray->vert_distance;
}

static void	small_distance(t_ray *ray)
{
	if (ray->horiz_distance == -1)
	{
		ray->side_flag = 2;
		ray->distance = ray->vert_distance;
	}
	else if (ray->vert_distance == -1)
	{
		ray->side_flag = 1;
		ray->distance = ray->horiz_distance;
	}
	else if (ray->vert_distance <= ray->horiz_distance)
	{
		ray->side_flag = 2;
		ray->distance = ray->vert_distance;
	}
	else if (ray->horiz_distance < ray->vert_distance)
	{
		ray->side_flag = 1;
		ray->distance = ray->horiz_distance;
	}
}

void	raycasting(t_maindata *data)
{
	t_ray	ray;
	int		column;

	column = 0;
	ray.rayangle = data->player.angle - (data->player.fov / 2);
	if (ray.rayangle < 0)
		ray.rayangle += 360;
	while (column <= WIDTH)
	{
		horiz_distance(data, &ray, ray.rayangle);
		vert_distance(data, &ray, ray.rayangle);
		real_distance(&ray, data);
		small_distance(&ray);
		draw_column(data, &ray, column);
		column++;
		ray.rayangle += data->player.angle_step;
		if (ray.rayangle >= 360)
			ray.rayangle -= 360;
	}
}
