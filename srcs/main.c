/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:33:15 by nal-haki          #+#    #+#             */
/*   Updated: 2025/03/26 22:43:04 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_config	scene_data;

	if (ac != 2)
		return (write(2, "Wrong arguments!\n", 17)
			, 1);
	file_parser(&scene_data, av[1]);
	start(&scene_data);
}
