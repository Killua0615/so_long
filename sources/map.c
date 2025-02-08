/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:44:30 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 12:04:29 by natsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	fill_map_lines(int fd, char **arr, int lines)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (i < lines && line)
	{
		arr[i] = line;
		i++;
		line = get_next_line(fd);
	}
	arr[i] = NULL;
	if (i < lines)
		return (0);
	return (1);
}

char	**read_map(char *file, int lines)
{
	int		fd;
	char	**arr;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!arr)
	{
		close(fd);
		return (NULL);
	}
	if (!fill_map_lines(fd, arr, lines))
	{
		free(arr);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (arr);
}

int	finish_game(t_game *game)
{
	int		i;
	void	*images[5];

	images[0] = game->img_1;
	images[1] = game->img_0;
	images[2] = game->img_c;
	images[3] = game->img_e;
	images[4] = game->img_p;

	i = -1;
	while (++i < 5)
	{
		if (images[i])
			mlx_destroy_image(game->mlx, images[i]);
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map.grid)
		arr_free(game->map.grid);
	exit(0);
}
