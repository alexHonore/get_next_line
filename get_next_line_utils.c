/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:57:32 by anshimiy          #+#    #+#             */
/*   Updated: 2022/04/22 11:36:19 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (0);
}

int	is_new_line(t_list *stash)
{
	int		i;
	t_list	*current;

	i = 0;
	current = ft_lstlast(stash);
	if (stash == NULL || current == 0)
		return (0);
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	add_to_stash(t_list **stash, char *buffer, int read_cpt)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	i = 0;
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * read_cpt + 1);
	if (new_node->content == NULL)
		return ;
	while (buffer[i] && i < read_cpt)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lstlast(*stash);
	last->next = new_node;
}

/* Calculates the number of chars in the current line, including the \n
   if there is one, and allocates the memory of it. */
void	generate_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc((len + 1) * sizeof(char));
}

unsigned int	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
