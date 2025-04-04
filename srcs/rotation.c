/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:49:07 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/02 17:20:16 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	radian(float degree)
{
	return (degree * M_PI / 180);
}

void	rotate(t_maindata *data)
{
	if (!data->keys[RIGHT_ARROW] && !data->keys[LEFT_ARROW])
		return ;
	if (data->keys[RIGHT_ARROW])
	{
		data->player.angle += ANGLE;
		if (data->player.angle >= 360)
			data->player.angle -= 360;
	}
	if (data->keys[LEFT_ARROW])
	{
		data->player.angle -= ANGLE;
		if (data->player.angle < 0)
			data->player.angle += 360;
	}
	data->keys[ROTATE_FLAG] = true;
}
