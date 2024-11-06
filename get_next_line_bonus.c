/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:53:10 by natallia          #+#    #+#             */
/*   Updated: 2024/11/06 21:39:07 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *stored_data, char *newline)
{
	size_t		i;
	size_t		len;
	char		*line;

	if (newline)
		len = newline - stored_data + 1;
	else
		len = ft_strlen(stored_data);
	line = malloc((len + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stored_data[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*extract_remainder(char *stored_data, char *newline, bool *error)
{
	char	*remainder;

	if (newline == NULL || *(newline + 1) == '\0')
		return (ft_free(&stored_data));
	remainder = ft_strdup(newline + 1);
	if (remainder == NULL)
	{
		*error = true;
		return (ft_free(&stored_data));
	}
	ft_free(&stored_data);
	return (remainder);
}

static char	*append_and_free(char *stored_data, char *buffer)
{
	size_t	stored_len;
	size_t	buffer_len;
	char	*new_data;

	stored_len = ft_strlen(stored_data);
	buffer_len = ft_strlen(buffer);
	new_data = malloc((stored_len + buffer_len + 1) * sizeof(char));
	if (new_data == NULL)
		return (ft_free(&stored_data));
	if (stored_data)
	{
		copy_string(new_data, stored_data);
		ft_free(&stored_data);
	}
	copy_string(new_data + stored_len, buffer);
	return (new_data);
}

static char	*read_and_store_data(int fd, char *stored_data)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (ft_free(&stored_data));
	bytes_read = 0;
	while ((stored_data && !find_newline(stored_data)) || !stored_data)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			ft_free(&buffer);
			if (bytes_read == -1)
				return (ft_free(&stored_data));
			else
				return (stored_data);
		}
		buffer[bytes_read] = '\0';
		stored_data = append_and_free(stored_data, buffer);
		if (stored_data == NULL)
			return (ft_free(&buffer));
	}
	ft_free (&buffer);
	return (stored_data);
}

static t_fd_list	*find_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*current;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	current = malloc(sizeof(t_fd_list));
	if (!current)
		return (NULL);
	current->fd = fd;
	current->stored_data = NULL;
	current->next = *head;
	*head = current;
	return (current);
}

static char	*remove_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*current;
	t_fd_list	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			ft_free(&current->stored_data);
			free(current);
			return (NULL);
		}
		prev = current;
		current = current->next;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	t_fd_list			*current_node;
	char				*current_line;
	char				*newline;
	bool				error_flag;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_node = find_fd_node(&fd_list, fd);
	if (!current_node)
		return (NULL);
	current_node->stored_data = read_and_store_data(fd, current_node->stored_data);
	if (current_node->stored_data == NULL)
		return (remove_fd_node(&fd_list, fd));
	newline = find_newline(current_node->stored_data);
	current_line = extract_line(current_node->stored_data, newline);
	if (current_line == NULL)
		return (remove_fd_node(&fd_list, fd));
	error_flag = 0;
	current_node->stored_data = extract_remainder(current_node->stored_data, newline, &error_flag);
	if (error_flag)
		return (remove_fd_node(&fd_list, fd), ft_free(&current_line));
	if (current_node->stored_data == NULL)
		remove_fd_node(&fd_list, fd);
	return (current_line);
}
