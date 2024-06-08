/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:23:41 by labdello          #+#    #+#             */
/*   Updated: 2024/06/08 12:22:14 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
size_t	ft_len(char *str, t_list *lst, char option)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (option == 's')
		while (str[i] != '\0')
			i++;
	else if (option == 'l')
	{
		while (lst != NULL)
        {
			lst = lst->next;
			i++;
        }
	}
	else if (option == 'b')
	{
		while (lst != NULL)
		{
			j = 0;
			while (lst->content[j] != '\0')
				j++;
			i += j;
			lst = lst->next;
		}
	}
	return (i);
}

char	*ft_lstjoin(t_list *lst)
{
	size_t	i;
	size_t	len;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_len(NULL, lst, 'b') + 1));
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (lst != NULL)
	{
		i = 0;
		len = ft_len(str, NULL, 's');
		while (lst->content[i] != '\0')
		{
			str[len + i] = lst->content[i];
			i++;
		}
		lst = lst->next;
	}
	str[len + i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	size_t		flag;
	t_list		*new;
	t_list		*stash;
	char		*content;
	char		*buffer;
	static char	*rest;

	stash = 0;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	*buffer = 0;
	if (rest)
	{
		new = ft_lstnew(rest);
		ft_lstadd_back(&stash, new);
	}
	while (read(fd, buffer, BUFFER_SIZE))
	{
		flag = ft_find_index(buffer, '\n') + 1;
		if (flag)
		{
			content = ft_strndup(buffer, flag);
			rest = ft_strndup(buffer + flag, ft_len(buffer, NULL, 's') - flag);
		}
		else
			content = ft_strndup(buffer, ft_len(buffer, NULL, 's'));
		new = ft_lstnew(content);
		if (!new)
		{
			ft_lstclear(&stash);
			free(content);
			return (NULL);
		}
		ft_lstadd_back(&stash, new);
		if (rest)
			break ;
	}
	content = ft_lstjoin(stash);
	ft_lstclear(&stash);
	return (content);
}

#include <fcntl.h>
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
