/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:23:53 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 23:17:48 by nateshim         ###   ########.fr       */
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
	// close(fd);
	// if (!check_file_extension(av[1]))
	// 	return (0);
	// fd = open(av[1], O_RDONLY);
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

// int	check_file_extension(char *file)
// {
// 	int	fd;

// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		ft_error("Failed to open file!");
// 		return (0);
// 	}
// 	close(fd);
// 	return (1);
// }
