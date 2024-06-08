/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:26:16 by labdello          #+#    #+#             */
/*   Updated: 2024/06/08 19:34:20 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strndup(char const *s, size_t n)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = (char *) malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	copy[0] = '\0';
	while (i < n && s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	find_index(char *str, char needle)
{
	size_t	i;

	i = 0;
	while (i + 1)
	{
		if (str[i] == needle)
			return (i);
		else if (str[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

static char	*ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*copy;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	copy = (char *) malloc(sizeof(char) * (total_len + 1));
	if (!copy)
		return (NULL);
	*copy = '\0';
	ft_strcat(copy, s1);
	ft_strcat(copy, s2);
	return (copy);
}
