/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:44:23 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/02 17:20:16 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**map_alloc(char *line, int fd, t_config *scene_data)
{
	char	**res;
	char	*new_line;
	char	*tmp;

	new_line = read_line(fd);
	while (new_line)
	{
		tmp = line;
		line = ft_strjoin(line, new_line);
		if (!line)
			return (free(new_line), error_handler
				("no memory", NULL, tmp, scene_data), NULL);
		free(tmp);
		free(new_line);
		new_line = read_line(fd);
	}
	res = ft_split(line, '\n');
	if (!res)
		error_handler("no memory", NULL, line, scene_data);
	return (free(line), res);
}

void	player_space_border_check(t_config *scene_data, int y, int x, char c)
{
	int		flag;
	char	*set;
	char	**map;

	flag = 0;
	map = scene_data->map;
	set = " 1";
	if (c == 'p')
		set = "10";
	if (map[y][x + 1] && !ft_strchr(set, map[y][x + 1]))
		flag = 1;
	else if (x > 0 && !ft_strchr(set, map[y][x - 1]))
		flag = 1;
	else if (y > 0 && (int)ft_strlen(map[y - 1]) >= x
		&& !ft_strchr(set, map[y - 1][x]))
		flag = 1;
	else if (map[y + 1] && (int)ft_strlen(map[y + 1]) >= x
		&& !ft_strchr(set, map[y + 1][x]))
		flag = 1;
	if (flag)
		error_handler("map is not fully surrounded by walls", NULL,
			NULL, scene_data);
}

void	set_player_angle(t_config *scene_data, char player_char, int y,
	int x)
{
	if (scene_data->player_start_angle != -1)
		error_handler("too many players in map",
			NULL, NULL, scene_data);
	if (player_char == 'N')
		scene_data->player_start_angle = N_ANGLE;
	else if (player_char == 'W')
		scene_data->player_start_angle = W_ANGLE;
	else if (player_char == 'E')
		scene_data->player_start_angle = E_ANGLE;
	else if (player_char == 'S')
		scene_data->player_start_angle = S_ANGLE;
	player_space_border_check(scene_data, y, x, 'p');
}

void	map_pars_helper(char **map, int y, int x, t_config *scene_data)
{
	if (!ft_strchr(" 01NSWE", map[y][x]))
		error_handler("use of invalid character in the map", NULL,
			NULL, scene_data);
	if (ft_strchr("SNWE", map[y][x]))
		set_player_angle(scene_data, map[y][x], y, x);
	if (map[y][x] == '0' && ((int)ft_strlen(map[y - 1]) <= x
		|| (int)ft_strlen(map[y + 1]) <= x))
		error_handler("map is not fully surrounded by walls",
			NULL, NULL, scene_data);
	if (map[y][x] == ' ')
		player_space_border_check(scene_data, y, x, ' ');
}

void	map_parser(char **map, t_config *scene_data)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		if ((y == 0 || !map[y + 1]) && top_bottom_check(map[y]))
			error_handler("map is not fully surrounded by walls",
				NULL, NULL, scene_data);
		while (map[y][++x])
		{
			if ((x == 0 || x == (int)ft_strlen(map[y]) - 1)
				&& !ft_strchr(" 1", map[y][x]))
				error_handler("map is not fully surrounded by walls",
					NULL, NULL, scene_data);
			map_pars_helper(map, y, x, scene_data);
			if (x > scene_data->map_width)
				scene_data->map_width = x + 1;
		}
	}
	if (scene_data->player_start_angle == -1)
		error_handler("no player found", NULL, NULL, scene_data);
}
