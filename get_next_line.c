/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:23:46 by anshimiy          #+#    #+#             */
/*   Updated: 2022/04/22 12:28:25 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	1) read_and_stash	==> read from fd and add to linked list
		|
		|----->	Uses read() to add characters to the stash.
	2) get_line			==> extract from stash to line
		|
		|----->	Extracts all characters from our stash and stores them in out line
				stopping after the first \n.
	3) clean_stash		==> free the stash list
		|
		|----->	After extracting the line that was read,
				we don't need those characters
 				anymore. This function clears the stash so only the characters that have
				not been returned at the end of get_next_line remain in our static stash.
*/
char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	get_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		ft_lstclear(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	ft_lstclear(t_list *lst)
{
	t_list	*current;
	t_list	*next;

	current = lst;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

void	read_and_stash(int fd, t_list **stash)
{
	char	*buffer;
	int		read_cpt;

	read_cpt = 1;
	while (!is_new_line(*stash) && read_cpt != 0)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return ;
		read_cpt = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && read_cpt == 0) || read_cpt < 0)
		{
			free(buffer);
			return ;
		}
		buffer[read_cpt] = '\0';
		add_to_stash(stash, buffer, read_cpt);
		free(buffer);
	}
}

/* Extracts all characters from our stash and stores them in outline.
 * stopping after the first \n */
void	get_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	j = 0;
	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

/* Clears the returned characters of the stash and let the non-returned*/
void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lstlast(*stash);
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(((ft_strlen(last->content) - i) + 1)
			* sizeof(char));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	ft_lstclear(*stash);
	*stash = clean_node;
}
