/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:24:00 by nal-haki          #+#    #+#             */
/*   Updated: 2025/03/26 23:37:50 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	corner_check_x(t_maindata *d, int px, int ix, int py)
{
	if (px > ix && wall_char(d, py, px - 1))
		return (true);
	if (px < ix && wall_char(d, py, px + 1))
		return (true);
	return (false);
}

static bool	corner_check_y(t_maindata *d, int py, int iy, int px)
{
	if (py > iy && wall_char(d, py - 1, px))
		return (true);
	if (py < iy && wall_char(d, py + 1, px))
		return (true);
	return (false);
}

static bool	check_corners(t_maindata *d, int ix, int iy)
{
	int	px;
	int	py;

	px = d->player.player_x / BLOCK_SIZE;
	py = d->player.player_y / BLOCK_SIZE;
	if (corner_check_x(d, px, ix, py) && corner_check_y(d, py, iy, px))
		return (true);
	return (false);
}

static int	get_grid_index(float pos, float prev, float size)
{
	int	index;

	index = pos / size;
	if ((int)pos % (int)size == 0 && prev > pos)
		index--;
	return (index);
}

bool	check_barriers(t_maindata *data, float x, float y)
{
	int		ix;
	int		iy;
	float	nx;
	float	ny;

	nx = data->player.player_x + x;
	ny = data->player.player_y + y;
	ix = get_grid_index(nx, data->player.player_x, BLOCK_SIZE);
	iy = get_grid_index(ny, data->player.player_y, BLOCK_SIZE);
	if (iy >= data->map_height || iy < 0 || ix < 0)
		return (true);
	if (ix >= (int)ft_strlen(data->map[iy]))
		return (true);
	if (!ft_strchr("NSEW0", data->map[iy][ix]))
		return (true);
	return (check_corners(data, ix, iy));
}
