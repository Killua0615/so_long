/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:44:23 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 12:07:16 by natsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
	arr_free(copied_map);
	return (result);
}
