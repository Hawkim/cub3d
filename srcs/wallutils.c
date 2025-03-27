/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:44:53 by nal-haki          #+#    #+#             */
/*   Updated: 2025/03/26 23:51:50 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	wall_char(t_maindata *data, int y, int x)
{
	return (data->map[y][x] == '1');
}
