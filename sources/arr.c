/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:23:53 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/09 14:45:20 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	**ft_arr_dup(char **arr)
{
	int		i;
	int		j;
	char	**new_arr;

	if (!arr || !arr[0])
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	new_arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_arr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_arr[j] = ft_strdup(arr[j]);
		if (!new_arr[j])
		{
			arr_free(new_arr);
			return (NULL);
		}
		j++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

int	init_game(int ac, char **av, t_game *game)
{
	int	fd;

	game->map.grid = NULL;
	game->move_count = 0;
	if (ac != 2)
		return (ft_error("Need only one argument"));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_error("Failed to open file!"));
	if (count_map(game, fd) != 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (check_map(game) != 0)
	{
		if (game->map.grid)
			arr_free(game->map.grid);
		return (0);
	}
	if (!collect_map(game, game->map.width, game->map.height))
		finish_game(game);
	return (1);
}

int	allocate_grid(t_game *game, int max_lines)
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
