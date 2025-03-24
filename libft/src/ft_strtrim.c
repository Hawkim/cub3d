/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:22:29 by nal-haki          #+#    #+#             */
/*   Updated: 2025/03/24 23:59:45 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*duplicator(const char *s, size_t i, size_t j)
{
	size_t	x;
	char	*trimed;

	x = 0;
	if (i == ft_strlen(s) || s[0] == '\0')
	{
		trimed = malloc(sizeof(char) * 1);
		if (!trimed)
			return (NULL);
		trimed[0] = '\0';
		return (trimed);
	}
	else
		trimed = malloc(sizeof(char) * (j - i + 2));
	if (!trimed)
		return (NULL);
	while (i <= j)
		trimed[x++] = s[i++];
	trimed[x] = '\0';
	return (trimed);
}

static int	trim_helper(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	long long	j;

	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && trim_helper(set, s1[i]))
		i++;
	while (j >= 0 && trim_helper(set, s1[j]))
		j--;
	return (duplicator(s1, i, j));
}
