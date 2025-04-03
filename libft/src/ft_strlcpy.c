/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:17:08 by nal-haki          #+#    #+#             */
/*   Updated: 2025/04/03 14:22:14 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dest, const char *srcs, size_t dstsize)
{
	size_t	i;
	size_t	count;

	if (!dest || !srcs)
		return (0);
	i = 0;
	count = 0;
	while (srcs[count] != '\0')
		count++;
	if (dstsize != 0)
	{
		while (srcs[i] != '\0' && i < (dstsize - 1))
		{
			dest[i] = srcs[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (count);
}
