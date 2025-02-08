/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:12:52 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 19:29:58 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	parse_map_char(t_game *game, int i, int j, int *p, int *e, int *c)
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
		(*p)++;
	else if (ch == 'E')
		(*e)++;
	else if (ch == 'C')
		(*c)++;
	return (1);
}

static int	scan_map_elements(t_game *game, int *p, int *e, int *c)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (!parse_map_char(game, i, j, p, e, c))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_counts(t_game *game, int p, int e, int c)
{
	if (p != 1)
	{
		ft_error("Error\nPlayer(P) must be exactly 1");
		return (0);
	}
	if (e != 1)
	{
		ft_error("Error\nExit(E) must be exactly 1");
		return (0);
	}
	if (c < 1)
	{
		ft_error("Error\nNo collectibles(C) found");
		return (0);
	}
	game->map.collectibles = c;
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
	int	p;
	int	e;
	int	c;

	p = 0;
	e = 0;
	c = 0;
	if (!scan_map_elements(game, &p, &e, &c))
		return (1);
	if (!check_counts(game, p, e, c))
		return (1);
	if (!check_path(game, c))
		return (1);
	return (0);
}
