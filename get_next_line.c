/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:10:50 by natallia          #+#    #+#             */
/*   Updated: 2024/11/05 22:10:58 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
	{
		free (stored_data);
		return (NULL);
	}
	remainder = ft_strdup(newline + 1);
	if (remainder == NULL)
	{
		*error = true;
		free (stored_data);
		return (NULL);
	}
	free (stored_data);
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
	bytes_read = 0;
	while (!find_newline(stored_data))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			if (bytes_read == -1)
			{
				free(stored_data);
				return (NULL);
			}
			return (stored_data);
		}
		buffer[bytes_read] = '\0';
		stored_data = append_and_free(stored_data, buffer);
	}
	free(buffer);
	return (stored_data);
}

char	*get_next_line(int fd)
{
	static char		*stored_data;
	char			*current_line;
	char			*newline;
	bool			error_flag;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored_data = read_and_store_data(fd, stored_data);
	if (stored_data == NULL)
		return (NULL);
	newline = find_newline(stored_data);
	current_line = extract_line(stored_data, newline);
	if (current_line == NULL)
	{
		free (stored_data);
		stored_data = NULL;
		return (NULL);
	}
	error_flag = 0;
	stored_data = extract_remainder(stored_data, newline, &error_flag);
	if (error_flag)
		return (NULL);
	return (current_line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	fd1 = open("tests/test.txt", O_RDONLY);
// 	fd2 = open("tests/test2.txt", O_RDONLY);
// 	fd3 = open("multiple_nl.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 7)
// 	{
// 		// line = get_next_line(fd1);
// 		// printf("line [%02d]: %s", i, line);
// 		// free(line);
// 		// line = get_next_line(fd2);
// 		// printf("line [%02d]: %s", i, line);
// 		// free(line);
// 		line = get_next_line(fd3);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
