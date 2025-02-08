/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:50:36 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 20:16:25 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	*get_tile_image(t_game *game, char tile)
{
	static void	*image_table[127];

	if (tile < 0 || tile > 127)
		return (NULL);
	if (!image_table['1'])
	{
		image_table['1'] = game->img_1;
		image_table['0'] = game->img_0;
		image_table['C'] = game->img_c;
		image_table['E'] = game->img_e;
		image_table['P'] = game->img_p;
	}
	if (!image_table[(int)tile])
		return (NULL);
	return (image_table[(int)tile]);
}

void	set_map(t_game *game)
{
	int		x;
	int		y;
	char	tile;
	void	*img;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			tile = game->map.grid[y][x];
			img = get_tile_image(game, tile);
			if (img)
				mlx_put_image_to_window(game->mlx, game->win, img, x
					* TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

static int	init_mlx_and_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_error("Failed to initialize MLX."));
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "So Long");
	if (!game->win)
		return (ft_error("Failed to create window."));
	return (1);
}

int	collect_map(t_game *game, int width, int height)
{
	if (!init_mlx_and_window(game))
		return (0);
	game->img_1 = mlx_xpm_file_to_image(game->mlx, "resources/1_grass.xpm",
			&width, &height);
	game->img_0 = mlx_xpm_file_to_image(game->mlx, "resources/0_born.xpm",
			&width, &height);
	game->img_c = mlx_xpm_file_to_image(game->mlx, "resources/c_hart.xpm",
			&width, &height);
	game->img_e = mlx_xpm_file_to_image(game->mlx, "resources/e_me.xpm", &width,
			&height);
	game->img_p = mlx_xpm_file_to_image(game->mlx, "resources/p_tama.xpm",
			&width, &height);
	if (!game->img_1 || !game->img_0 || !game->img_c || !game->img_e
		|| !game->img_p)
		return (ft_error("Failed to load XPM file!"));
	return (1);
}

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	game.move_count = 0;
	game.map.grid = NULL;
	if (ac != 2)
		return (ft_error("Need only one argument"));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_error("Failed to open file!");
		return (0);
	}
	if (count_map(&game, fd) != 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (check_map(&game) != 0)
	{
		if (game.map.grid)
			arr_free(game.map.grid);
		return (1);
	}
	if (!collect_map(&game, game.map.width, game.map.height))
		finish_game(&game);
	set_map(&game);
	mlx_hook(game.win, 2, 1L << 0, on_keypress, &game);
	mlx_hook(game.win, 17, 0, finish_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
