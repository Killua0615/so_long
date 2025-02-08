/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:45:01 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 18:45:11 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static char	*extract_line(char *saved)
{
	int		len;
	char	*line;

	len = 0;
	if (!saved || !saved[len])
		return (NULL);
	while (saved[len] && saved[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	len = 0;
	while (saved[len] && saved[len] != '\n')
	{
		line[len] = saved[len];
		len++;
	}
	if (saved[len] == '\n')
	{
		line[len] = '\n';
		len++;
	}
	line[len] = '\0';
	return (line);
}

static char	*update_saved(char *saved)
{
	int		start;
	int		i;
	char	*new_saved;

	start = 0;
	i = 0;
	while (saved[start] && saved[start] != '\n')
		start++;
	if (!saved[start])
	{
		free(saved);
		return (NULL);
	}
	start++;
	new_saved = (char *)malloc(sizeof(char) * (ft_strlen(saved) - start + 1));
	if (!new_saved)
		return (NULL);
	while (saved[start])
		new_saved[i++] = saved[start++];
	new_saved[i] = '\0';
	free(saved);
	return (new_saved);
}

static char	*read_to_saved(int fd, char *buffer, char **saved)
{
	ssize_t	bytes_read;

	while (!gnl_ft_strchr(*saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			if (bytes_read == 0)
				return (*saved);
			else
				return (NULL);
		}
		buffer[bytes_read] = '\0';
		*saved = gnl_ft_strjoin(*saved, buffer);
		if (!*saved)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (*saved);
}

char	*get_next_line(int fd)
{
	static char	*saved = NULL;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!read_to_saved(fd, buffer, &saved))
		return (NULL);
	line = extract_line(saved);
	saved = update_saved(saved);
	return (line);
}
