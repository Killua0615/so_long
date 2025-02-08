/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:43:35 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 20:13:48 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	allocate_grid(t_game *game, int max_lines)
{
	char	**grid;

	grid = malloc(sizeof(char *) * (max_lines + 1));
	if (!grid)
	{
		ft_error("Error\nFailed to allocate memory for grid");
		free(grid);
		return (0);
	}
	game->map.grid = grid;
	game->map.height = 0;
	game->map.width = 0;
	return (1);
}

static void	adjust_line_len(char *line, int *length)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	*length = i;
	if (*length > 0 && line[*length - 1] == '\n')
	{
		line[*length - 1] = '\0';
		(*length)--;
	}
}

static int	process_line(t_game *game, char *line, int index)
{
	int	length;

	length = 0;
	adjust_line_len(line, &length);
	if (index == 0)
	{
		game->map.width = length;
		if (length == 0)
		{
			free(line);
			ft_error("Error\nMap's first line is empty");
			return (0);
		}
	}
	else if (length != game->map.width)
	{
		free(line);
		ft_error("Error\nMap is not rectangle");
		return (0);
	}
	game->map.grid[index] = line;
	game->map.height++;
	return (1);
}

static int	read_lines_loop(t_game *game, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	if (!line)
	{
		ft_error("Error\nFile is empty!");
		return (0);
	}
	while (line)
	{
		if (!process_line(game, line, i))
		{
			while (i > 0)
			{
				--i;
				free(game->map.grid[i]);
				game->map.grid[i] = NULL;
			}
			return (0);
		}
		i++;
		line = get_next_line(fd);
	}
	game->map.grid[i] = NULL;
	return (1);
}

int	count_map(t_game *game, int fd)
{
	int	max_lines;

	max_lines = 10000;
	if (!allocate_grid(game, max_lines))
		return (1);
	if (!read_lines_loop(game, fd))
	{
		free(game->map.grid);
		game->map.grid = NULL;
		return (1);
	}
	return (0);
}
