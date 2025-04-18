/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:52:58 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/03 14:12:43 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_height_width(t_config *scene_data)
{
	int	i;

	i = 0;
	while (scene_data->map[i])
	{
		scene_data->map_height++;
		if ((int)ft_strlen(scene_data->map[i]) > scene_data->map_width)
			scene_data->map_width = ft_strlen(scene_data->map[i]);
		i++;
	}
}

void	check_prev_members(t_config *scene_data, char *line)
{
	int	i;

	i = 0;
	while (i <= 3)
	{
		if (!scene_data->textures_paths[i])
			error_handler("wrong textures path", NULL, line, scene_data);
		ft_access(scene_data->textures_paths[i], scene_data, line, i);
		i++;
	}
	if (scene_data->ceiling_color == -1)
		error_handler("wrong ceiling color", NULL, line, scene_data);
	if (scene_data->floor_color == -1)
		error_handler("wrong floor color", NULL, line, scene_data);
}

int	is_map_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(" 10NSWE\n", str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	top_bottom_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	open_cub_file(char *file)
{
	int		fd;
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
		error_handler("file must have .cub extension", NULL, NULL, NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_handler("cannot open the provided file", NULL, NULL, NULL);
	return (fd);
}
