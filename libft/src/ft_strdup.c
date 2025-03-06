/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:56:16 by nal-haki          #+#    #+#             */
/*   Updated: 2025/03/06 15:03:03 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *srcs)
{
	int		len;
	char	*dest;

	if (!srcs)
		return (NULL);
	len = ft_strlen((char *)srcs);
	dest = malloc (sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, srcs, len);
	dest[len] = '\0';
	return (dest);
}
