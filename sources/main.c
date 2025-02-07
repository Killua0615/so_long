#include "../so_long.h"

void	set_map_design(t_game *game, int x, int y, char tile)
{
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			tile = game->map.grid[y][x];
			if (tile == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x
					* TILE_SIZE, y * TILE_SIZE);
			else if (tile == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->img_floor, x
					* TILE_SIZE, y * TILE_SIZE);
			else if (tile == 'C')
				mlx_put_image_to_window(game->mlx, game->win,
					game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
			else if (tile == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->img_exit, x
					* TILE_SIZE, y * TILE_SIZE);
			else if (tile == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->img_player,
					x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

int	init_graphics(t_game *game, int width, int height)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_error("Failed to initialize MLX."));
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "So Long");
	if (!game->win)
		return (ft_error("Failed to create window."));
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "resources/1_grass.xpm",
			&width, &height);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "resources/0_born.xpm",
			&width, &height);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx,
			"resources/c_hart.xpm", &width, &height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "resources/e_me.xpm",
			&width, &height);
	game->img_player = mlx_xpm_file_to_image(game->mlx, "resources/p_tama.xpm",
			&width, &height);
	if (!game->img_wall || !game->img_floor || !game->img_collectible
		|| !game->img_exit || !game->img_player)
		return (ft_error("Failed to load XPM file!"));
	return (1);
}

int	main(int ac, char **av)
{
	int fd;
	t_game	game;

	game.move_count = 0;
	if (ac != 2)
		return (ft_error("Need only one argument"));

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_error("Filename must end in .ber, Invalid file format!");
		return (0);
	}
	if (count_map(&game, fd) != 0)
	    return (1);
	close(fd);
	if (check_map(&game) != 0)
	    return (1);
	close(fd);
	if (!init_graphics(&game, game.map.width, game.map.height))
		close_game(&game);
	set_map_design(&game, 0, 0, ' ');
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
