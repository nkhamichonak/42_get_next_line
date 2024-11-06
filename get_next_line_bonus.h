/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:47:30 by natallia          #+#    #+#             */
/*   Updated: 2024/11/06 21:37:05 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_fd_list
{
	int					fd;
	char				*stored_data;
	struct s_fd_list	*next;
}	t_fd_list;

char		*get_next_line(int fd);
size_t		ft_strlen(const char *str);
char		*find_newline(char *str);
void		copy_string(char *dest, const char *src);
char		*ft_strdup(const char *s);
char		*ft_free(char **str);

#endif
