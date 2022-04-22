/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:57:04 by anshimiy          #+#    #+#             */
/*   Updated: 2022/04/22 11:38:03 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE = 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
int					is_new_line(t_list *stash);
void				read_and_stash(int fd, t_list **stash);
void				get_line(t_list *stash, char **line);
void				clean_stash(t_list **stash);
void				ft_lstclear(t_list *lst);
void				add_to_stash(t_list **stash, char *buffer, int read_cpt);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, size_t n);
t_list				*ft_lstlast(t_list *lst);
void				extract_line(t_list *stash, char **line);
void				clean_stash(t_list **stash);
unsigned int		ft_strlen(const char *s);
void				generate_line(char **line, t_list *stash);

#endif