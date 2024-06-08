/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:23:41 by labdello          #+#    #+#             */
/*   Updated: 2024/06/08 19:31:31 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(int fd, char *rest, char *buffer)
{
	char		*tmp;
	ssize_t		read_len;

	read_len = 1;
	while (read_len)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(rest);
			return (NULL);
		}
		if (read_len == 0)
			break ;
		buffer[read_len] = '\0';
		tmp = rest;
		rest = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (find_index(buffer, '\n'))
			break ;
	}
	return (rest);
}

static char	*trim_line(char *line)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = find_index(line, '\n');
	len = ft_strlen(line);
	if (i == len || line[i + 1] == '\0')
		return (NULL);
	i += 1;
	str = ft_strndup(line + i, len - i);
	line[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*buffer;

	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(rest);
		free(buffer);
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	if (!rest)
		rest = ft_strndup("", 0);
	line = get_line(fd, rest, buffer);
	rest = trim_line(line);
	free(buffer);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *str1 = get_next_line(fd);
	printf("%s", str1);
	char *str2 = get_next_line(fd);
	printf("%s", str2);
	free(str1);
	free(str2);
}
