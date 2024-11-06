/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:11:42 by natallia          #+#    #+#             */
/*   Updated: 2024/11/06 17:51:03 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char		*get_next_line(int fd);
size_t		ft_strlen(const char *str);
char		*find_newline(char *str);
void		copy_string(char *dest, const char *src);
char		*ft_strdup(const char *s);
char		*ft_free(char **str);

#endif
