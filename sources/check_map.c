/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:12:52 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 21:57:44 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	parse_map_char(t_game *game, int i, int j, t_counts *cnt)
{
	char	ch;

	ch = game->map.grid[i][j];
	if (!ft_strchr("01CEP", ch))
	{
		ft_error("Error\nInvalid map letter");
		return (0);
	}
	if ((i == 0 || i == game->map.height - 1 || j == 0 || j == game->map.width
			- 1) && ch != '1')
	{
		ft_error("Error\nMap isn't be closed by walls(1)");
		return (0);
	}
	if (ch == 'P')
		cnt->p++;
	else if (ch == 'E')
		cnt->e++;
	else if (ch == 'C')
		cnt->c++;
	return (1);
}

static int	scan_map_elements(t_game *game, t_counts *cnt)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (!parse_map_char(game, i, j, cnt))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_counts(t_game *game, t_counts *cnt)
{
	if (cnt->p != 1)
	{
		ft_error("Error\nPlayer(P) must be exactly 1");
		return (0);
	}
	if (cnt->e != 1)
	{
		ft_error("Error\nExit(E) must be exactly 1");
		return (0);
	}
	if (cnt->c < 1)
	{
		ft_error("Error\nNo collectibles(C) found");
		return (0);
	}
	game->map.collectibles = cnt->c;
	game->map.exits = 1;
	return (1);
}

static int	check_path(t_game *game, int c)
{
	int	result;
	int	needed;

	result = finds_player(&game->map);
	needed = c + 1;
	if (result < needed)
	{
		ft_error("Error\nNo valid path from P to all C and E");
		return (0);
	}
	return (1);
}

int	check_map(t_game *game)
{
	t_counts	cnt;

	cnt.p = 0;
	cnt.e = 0;
	cnt.c = 0;
	if (!scan_map_elements(game, &cnt))
		return (1);
	if (!check_counts(game, &cnt))
		return (1);
	if (!check_path(game, cnt.c))
		return (1);
	return (0);
}
