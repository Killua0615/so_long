/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:44:35 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 11:03:16 by natsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	update_current_cell(int x, int y, t_game *game)
{
	if (game->map.grid[y][x] == '0' || game->map.grid[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->img_floor, x
			* TILE_SIZE, y * TILE_SIZE);
	else if (game->map.grid[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->img_exit, x
			* TILE_SIZE, y * TILE_SIZE);
}

void	convert_moves_to_string(int move_count, char *buffer)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (move_count > 0)
	{
		buffer[i++] = (move_count % 10) + '0';
		move_count /= 10;
	}
	buffer[i] = '\0';
	j = 0;
	while (j < --i)
	{
		tmp = buffer[j];
		buffer[j++] = buffer[i];
		buffer[i] = tmp;
	}
}

void	print_moved(int move_count)
{
	char	buffer[12];

	convert_moves_to_string(move_count, buffer);
	ft_printf("Moved: %s\n", buffer);
	// write(1, "Moved: ", 7);
	// write(1, buffer, ft_strlen(buffer));
	// write(1, "\n", 1);
}

void	player_movement(t_game *game, int dx, int dy)
{
	char	destination;
	int		new_x;
	int		new_y;

	new_x = game->map.player_x + dx;
	new_y = game->map.player_y + dy;
	destination = game->map.grid[new_y][new_x];
	if (destination == '1')
		return ;
	if (destination == 'E' && game->map.collectibles == 0)
		finish_game(game);
	if (destination == 'C')
	{
		game->map.collectibles--;
		game->map.grid[new_y][new_x] = '0';
	}
	game->move_count++;
	print_moved(game->move_count);
	update_current_cell(game->map.player_x, game->map.player_y, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img_player, new_x
		* TILE_SIZE, new_y * TILE_SIZE);
	game->map.player_x = new_x;
	game->map.player_y = new_y;
}

int	handle_keypress(int key, t_game *game)
{
	if (key == KEY_ESC)
		finish_game(game);
	else if (key == KEY_W || key == KEY_UP)
		player_movement(game, 0, -1);
	else if (key == KEY_S || key == KEY_DOWN)
		player_movement(game, 0, 1);
	else if (key == KEY_A || key == KEY_LEFT)
		player_movement(game, -1, 0);
	else if (key == KEY_D || key == KEY_RIGHT)
		player_movement(game, 1, 0);
	return (0);
}
