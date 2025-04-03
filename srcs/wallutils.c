/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:44:53 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/03 15:39:33 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	wall_char(t_maindata *data, int y, int x)
{
	return (data->map[y][x] == '1');
}

char	*trim_whitespace(char *str)
{
	char	*end;

	while (ft_space((unsigned char)*str))
		str++;
	if (*str == '\0')
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_space((unsigned char)*end))
		end--;
	end[1] = '\0';
	return (str);
}
