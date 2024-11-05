/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:10:50 by natallia          #+#    #+#             */
/*   Updated: 2024/11/05 09:56:37 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_and_free(char *stored_data, char *buffer)
{
	size_t	stored_len;
	size_t	buffer_len;
	char	*new_data;

	stored_len = strlen(stored_data);
	buffer_len = strlen(buffer);
	new_data = malloc((stored_len + buffer_len + 1) * sizeof(char));
	if (new_data == NULL)
	{
		free (stored_data);
		return (NULL);
	}
	if (stored_data)
	{
		copy_string(new_data, stored_data);
		free(stored_data);
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
		return (NULL);
	bytes_read = 1;
	while (!find_newline(stored_data) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stored_data = append_and_free(stored_data, buffer);
	}
	free (buffer);
	return (stored_data);
}

char	*extract_line(char *stored_data, char *newline)
{
	size_t		i;
	size_t		len;
	char		*line;

	if (newline)
		len = newline - stored_data + 1;
	else
		len = strlen(stored_data);
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

char	*extract_remainder(char *stored_data, char *newline)
{
	size_t	rem_len;
	char	*remainder;
	char	*ptr;

	ptr = stored_data;
	while (*ptr)
		ptr++;
	if (newline)
		rem_len = ptr - newline;
	else
	{
		free (stored_data);
		return (NULL);
	}
	remainder = malloc((rem_len + 1) * sizeof(char));
	if (remainder == NULL)
		return (NULL);
	while ()


}

char	*get_next_line(int fd)
{
	static char		*stored_data;
	char			*current_line;

	stored_data = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);
	stored_data = read_and_store_data(fd, stored_data);
	if (stored_data == NULL)
		return (NULL);
	current_line = extract_line(stored_data, find_newline(stored_data));
	if (current_line == NULL)
	{
		free (stored_data);
		return (NULL);
	}
	stored_data = extract_remainder(stored_data, find_newline(stored_data));
	if (find_newline && stored_data == NULL)
		return (NULL);
	return (current_line);
}
