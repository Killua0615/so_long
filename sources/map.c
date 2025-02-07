/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:44:30 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/07 23:16:08 by natsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	count_lines(char *file)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		count_line;
	ssize_t	i;

	fd = open(file, O_RDONLY);
	count_line = 1;
	bytes_read = 1;
	while (!(fd < 0) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		i = -1;
		while (++i < bytes_read)
		{
			if (count_line == INT_MAX && buffer[i] == '\n')
				return (-2);
			if (buffer[i] == '\n')
				count_line++;
		}
	}
	close(fd);
	if (fd < 0 || bytes_read < 0)
		return (-1);
	return (count_line);
}

char	**read_map(char *file, int lines)
{
	int		fd;
	char	**arr;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!arr)
	{
		close(fd);
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (i < lines && line)
	{
		arr[i] = line;
		i++;
		line = get_next_line(fd);
	}
	arr[i] = NULL;
	close(fd);
	return (arr);
}

int	is_valid_map(t_map *map)
{
	if (!is_rectangular(map))
		return (ft_error("Map is not rectangular.\n"));
	if (!is_surrounded_by_walls(map))
		return (ft_error("Map is not surrounded by walls.\n"));
	if (!is_enough_elements(map))
		return (ft_error("Map elements are invalid.\n"));
	if (finds_player(map) != ((map->exits) + (map->collectibles)))
		return (ft_error("No valid path in the map.\n"));
	return (1);
}

// int	grid_of_the_map(char *file, t_map *map)
// {
// 	map->height = count_lines(file);
// 	if (map->height == -1)
// 		return (ft_error("Failed to open or read file."));
// 	if (map->height == -2 || map->height <= 2)
// 		return (ft_error("Too small or too big map!"));
// 	map->grid = read_map(file, map->height);
// 	if (!map->grid)
// 		return (ft_error("Cannot read map."));
// 	map->width = ft_strlen_line(map->grid[0]);
// 	if (map->width == -1)
// 	{
// 		ft_free(map->grid);
// 		return (ft_error("Map is too big!"));
// 	}
// 	if (!is_valid_map(map))
// 	{
// 		ft_free(map->grid);
// 		return (0);
// 	}
// 	return (1);
// }

int	close_game(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map.grid)
		ft_free(game->map.grid);
	exit(0);
	return (0);
}
