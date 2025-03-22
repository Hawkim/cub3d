/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:14 by nal-haki          #+#    #+#             */
/*   Updated: 2024/12/19 13:50:42 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	intitialize_keyflags(t_maindata *data)
{
	data->keys[RIGHT_FLAG] = false;
	data->keys[LEFT_FLAG] = false;
	data->keys[W_FLAG] = false;
	data->keys[S_FLAG] = false;
	data->keys[D_FLAG] = false;
	data->keys[A_FLAG] = false;
	data->keys[CLOSE_FLAG] = false;
	data->keys[ROTATE_FLAG] = false;
	data->keys[MOVE_FLAG] = false;
}

int	ft_press_key(int key, t_maindata *data)
{
	if (key == RIGHT)
		data->keys[RIGHT_FLAG] = true;
	if (key == LEFT)
		data->keys[LEFT_FLAG] = true;
	if (key == W)
		data->keys[W_FLAG] = true;
	if (key == S)
		data->keys[S_FLAG] = true;
	if (key == D)
		data->keys[D_FLAG] = true;
	if (key == A)
		data->keys[A_FLAG] = true;
	if (key == CLOSE)
		data->keys[CLOSE_FLAG] = true;
	return (false);
}

int	ft_release_key(int key, t_maindata *data)
{
	if (key == RIGHT)
		data->keys[RIGHT_FLAG] = false;
	if (key == LEFT)
		data->keys[LEFT_FLAG] = false;
	if (key == W)
		data->keys[W_FLAG] = false;
	if (key == S)
		data->keys[S_FLAG] = false;
	if (key == D)
		data->keys[D_FLAG] = false;
	if (key == A)
		data->keys[A_FLAG] = false;
	return (0);
}
