/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:26:16 by labdello          #+#    #+#             */
/*   Updated: 2024/06/07 11:57:49 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_strndup(char *str, size_t n)
{
	size_t  i;
	char    *copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	copy[0] = '\0';
	while (str[i] != '\0' && i < n)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	ft_find_index(char *str, char needle)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == needle)
			return (i);
		i++;
	}
	return (0);
}

t_list  *ft_lstlast(t_list *lst)
{
        if (!lst)
                return (NULL);
        while (lst->next != NULL)
                lst = lst->next;
        return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_element;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last_element = ft_lstlast(*(lst));
		last_element->next = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = (t_list *)malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->next = NULL;
	element->content = content;
	return (element);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}
