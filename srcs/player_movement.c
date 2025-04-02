/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:49:46 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/02 17:20:16 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	w_moves(t_maindata *data)
{
	float	delta_x;
	float	delta_y;
	float	speed;

	if (data->keys[W_FLAG])
	{
		speed = (float)BLOCK_SIZE / SPEED_DIV;
		delta_x = (cos(radian(data->player.angle)) * speed);
		delta_y = (sin(radian(data->player.angle)) * speed);
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
		data->keys[MOVE_FLAG] = true;
	}
}

static void	s_moves(t_maindata *data)
{
	float	delta_x;
	float	delta_y;
	float	speed;

	if (data->keys[S_FLAG])
	{
		speed = (float)BLOCK_SIZE / SPEED_DIV;
		delta_x = (cos(radian(data->player.angle)) * speed) * -1;
		delta_y = (sin(radian(data->player.angle)) * speed) * -1;
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
		data->keys[MOVE_FLAG] = true;
	}
}

static void	d_moves(t_maindata *data)
{
	float	delta_x;
	float	delta_y;
	float	speed;

	if (data->keys[D_FLAG])
	{
		speed = (float)BLOCK_SIZE / SPEED_DIV;
		delta_x = (sin(radian(data->player.angle)) * speed) * -1;
		delta_y = (cos(radian(data->player.angle)) * speed);
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
		data->keys[MOVE_FLAG] = true;
	}
}

static void	a_moves(t_maindata *data)
{
	float	delta_x;
	float	delta_y;
	float	speed;

	if (data->keys[A_FLAG])
	{
		speed = (float)BLOCK_SIZE / SPEED_DIV;
		delta_x = (sin(radian(data->player.angle)) * speed);
		delta_y = (cos(radian(data->player.angle)) * speed) * -1;
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
		data->keys[MOVE_FLAG] = true;
	}
}

void	ft_moveplayer(t_maindata *data)
{
	if (!data->keys[W_FLAG] && !data->keys[S_FLAG] && !data->keys[D_FLAG]
		&& !data->keys[A_FLAG])
		return ;
	w_moves(data);
	s_moves(data);
	d_moves(data);
	a_moves(data);
}
