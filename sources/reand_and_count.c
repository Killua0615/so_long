/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reand_and_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:53:01 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 18:53:03 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	read_and_count_lines(int fd, int *count_line)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	ssize_t	i;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read < 0)
			return (-1);
		i = -1;
		while (++i < bytes_read)
		{
			if (*count_line == INT_MAX && buffer[i] == '\n')
				return (-2);
			if (buffer[i] == '\n')
				(*count_line)++;
		}
	}
	return (1);
}

int	count_lines(char *file)
{
	int	fd;
	int	ret;
	int	count_line;

	count_line = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	ret = read_and_count_lines(fd, &count_line);
	close(fd);
	if (ret < 0)
		return (ret);
	return (count_line);
}
