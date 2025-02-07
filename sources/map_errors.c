/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:44:23 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/07 23:16:08 by natsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	is_rectangular(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->width != ft_strlen_line(map->grid[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_surrounded_by_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if ((map->grid[i][0] != '1') || (map->grid[i][map->width - 1] != '1'))
			return (0);
		i++;
	}
	i = 0;
	while (i < map->width)
	{
		if ((map->grid[0][i] != '1') || (map->grid[map->height - 1][i] != '1'))
			return (0);
		i++;
	}
	return (1);
}

int	is_enough_elements(t_map *map)
{
	int	i;
	int	j;

	map->exits = 0;
	map->collectibles = 0;
	map->players = 0;
	i = -1;
	while (++i < map->height)
	{
		j = 0;
		while (++j < map->width)
		{
			if (map->grid[i][j] == 'E')
				map->exits++;
			else if (map->grid[i][j] == 'C')
				map->collectibles++;
			else if (map->grid[i][j] == 'P')
				map->players++;
			else if (map->grid[i][j] != '0' && map->grid[i][j] != '1')
				return (0);
		}
	}
	if (map->exits != 1 || map->players != 1 || map->collectibles < 1)
		return (0);
	return (1);
}

int	walkable_path(char **map, int x, int y, t_map *m)
{
	int	count;

	if (x < 0 || y < 0 || y >= m->height || x >= m->width || map[y][x] == '1')
		return (0);
	count = 0;
	if (map[y][x] == 'E' || map[y][x] == 'C')
		count++;
	map[y][x] = '1';
	count += walkable_path(map, x + 1, y, m);
	count += walkable_path(map, x, y + 1, m);
	count += walkable_path(map, x - 1, y, m);
	count += walkable_path(map, x, y - 1, m);
	return (count);
}

int	finds_player(t_map *map)
{
	char	**copied_map;
	int		start_x;
	int		start_y;
	int		result;

	copied_map = ft_arr_dup(map->grid);
	if (!copied_map)
		return (0);
	start_y = map->height;
	while (--start_y >= 0)
	{
		start_x = map->width;
		while (--start_x >= 0)
		{
			if (copied_map[start_y][start_x] == 'P')
				break ;
		}
		if (start_x >= 0 && copied_map[start_y][start_x] == 'P')
			break ;
	}
	map->player_x = start_x;
	map->player_y = start_y;
	result = walkable_path(copied_map, start_x, start_y, map);
	ft_free(copied_map);
	return (result);
}
