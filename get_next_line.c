/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:23:41 by labdello          #+#    #+#             */
/*   Updated: 2024/06/06 19:25:35 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_getlen(char *str, t_list *lst, char option)
{
	size_t	i;

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
			while (lst->content[i] != '\0')
				i++;
			lst = lst->next;
		}
	}
	return (i);
}

#include <stdio.h>
char	*ft_lstjoin(t_list *lst)
{
	size_t	i;
	char	*str;

	str = (char *)malloc(1000 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			str[ft_getlen(str, NULL, 's') + i] = lst->content[i];
			i++;
		}
		lst = lst->next;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	t_list	*new;
	char	*content;
	void	*buffer[BUFFER_SIZE];
	t_list	*stash;

	stash = 0;
	while (read(fd, buffer, BUFFER_SIZE))
	{
		// write(1, (char *)buffer, BUFFER_SIZE);
		content = ft_strdup((char *)buffer);
		new = ft_lstnew(content);
		if (!new)
		{
			ft_lstclear(&stash);
			free(content);
			return (NULL);
		}
		ft_lstadd_back(&stash, new);
		if (ft_find_index(content, '\n'))
			break ;
	}
	return (ft_lstjoin(stash));
}

#include <fcntl.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}
