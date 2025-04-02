/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:01:07 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/02 18:38:19 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_memory(void *mlx, t_texture *my_textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(mlx, my_textures[i].img);
		i++;
	}
}

static int	get_cords_color(t_texture *img, int x, int y)
{
	char	*dst;

	dst = img->iter + (y * img->line_length + x * (img->pixel_bits / 8));
	return (*(int *)dst);
}

void	initialize_textures(t_maindata *data, t_config *parsed_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->wall_textures[i].img = mlx_xpm_file_to_image(data->mlx,
				parsed_data->textures_paths[i], &data->wall_textures[i].width,
				&data->wall_textures[i].height);
		data->wall_textures[i].iter = mlx_get_data_addr
			(data->wall_textures[i].img, &data->wall_textures[i].pixel_bits,
				&data->wall_textures[i].line_length,
				&data->wall_textures[i].endianess);
		i++;
	}
}

void	get_texture_color(t_maindata *data, t_ray *ray, int current_y)
{
	float	x_scale;
	float	y_scale;
	int		current_x;

	current_x = 0;
	x_scale = (float)data->wall_textures[ray->texture_index].width / BLOCK_SIZE;
	y_scale = (float)data->wall_textures[ray->texture_index]
		.height / ray->height;
	if (ray->texture_index == NORTH_INDEX)
		current_x = (int)ray->horiz_x % BLOCK_SIZE;
	else if (ray->texture_index == SOUTH_INDEX)
		current_x = BLOCK_SIZE - ((int)ray->horiz_x % BLOCK_SIZE);
	else if (ray->texture_index == EAST_INDEX)
		current_x = (int)ray->vertical_y % BLOCK_SIZE;
	else if (ray->texture_index == WEST_INDEX)
		current_x = BLOCK_SIZE - ((int)ray->vertical_y % BLOCK_SIZE);
	ray->curr_color = get_cords_color(&data->wall_textures[ray->texture_index],
			current_x * x_scale, current_y * y_scale);
}
