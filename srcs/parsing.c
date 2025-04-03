/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:52:51 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/03 15:32:16 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_color_format(char *str)
{
	int	digit_count;
	int	pos;

	pos = 0;
	digit_count = 0;
	while (str[pos] == '0' || str[pos] == ' ')
		pos++;
	while (str[pos])
	{
		if (ft_isdigit(str[pos]))
			digit_count++;
		else if (str[pos] != ' ' && str[pos] != '\n')
			return (1);
		pos++;
	}
	if (digit_count > 3 || ft_atoi(str) > 255)
		return (1);
	return (0);
}

static void	parse_color(t_config *data, char *line, int is_floor)
{
	char	*color_ptr;
	int		idx;
	char	**rgb;

	color_ptr = (char *)&data->ceiling_color;
	if (is_floor)
		color_ptr = (char *)&data->floor_color;
	if (*color_ptr != -1)
		error_handler("duplicate element", NULL, line, data);
	rgb = ft_split(line + 1, ',');
	if (strings_len(rgb) != 3)
		error_handler("floor and ceiling must be in R,G,B format",
			rgb, line, data);
	idx = 0;
	while (idx < 3)
		if (check_color_format(rgb[idx++]))
			error_handler("R,G,B must be in [0,255]", rgb, NULL, data);
	while (--idx >= 0)
		*color_ptr++ = ft_atoi(rgb[idx]);
	*color_ptr = 0;
	strings_free(rgb);
}

static void	store_texture(char **words, t_config *data, char *line)
{
	int		idx;
	char	*types[5];

	types[0] = "NO";
	types[1] = "SO";
	types[2] = "WE";
	types[3] = "EA";
	types[4] = NULL;
	idx = 0;
	while (types[idx] && ft_strncmp(words[0], types[idx], 3))
		idx++;
	if (idx < 4)
	{
		if (data->textures_paths[idx])
			error_handler("duplicate element", words, line, data);
		data->textures_paths[idx] = ft_strtrim(words[1], "\n");
		return ;
	}
	if (!ft_strncmp(words[0], "F", 2) || !ft_strncmp(words[0], "C", 2))
		return (parse_color(data, line, words[0][0] == 'F'));
	error_handler("unknown element", words, line, data);
}

static void	parse_line(char *line, t_config *data, int *map_started)
{
	char	**words;

	if (line[0] == '\n')
		return ;
	if (is_map_line(line))
	{
		*map_started = 1;
		return ;
	}
	line = trim_whitespace(line);
	words = ft_split(line, ' ');
	if (!words)
		error_handler("no memory", NULL, line, data);
	if (strings_len(words) != 2)
		error_handler("each element must be exact", words, line, data);
	store_texture(words, data, line);
	strings_free(words);
}

void	file_parser(t_config *data, char *file_path)
{
	int		map_flag;
	int		fd;
	char	*line;

	map_flag = 0;
	data_init(data);
	fd = open_cub_file(file_path);
	if (fd < 0)
		error_handler("file open failed", NULL, NULL, data);
	while (1)
	{
		line = read_line(fd);
		if (!line)
			break ;
		parse_line(line, data, &map_flag);
		if (map_flag)
			break ;
		free(line);
	}
	if (!map_flag)
		error_handler("no map in file", NULL, line, data);
	check_prev_members(data, line);
	data->map = map_alloc(line, fd, data);
	map_parser(data->map, data);
	set_height_width(data);
}
