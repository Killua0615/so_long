/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:44:35 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 13:37:32 by natsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void draw_cell(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == '0' || game->map.grid[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_0, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map.grid[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_e, x * TILE_SIZE, y * TILE_SIZE);
}

static void int_to_str(int move_count, char *buffer)
{
	int		i;
	int		j;
	int		tmp_count;
	char	tmp;

	i = 0;
	tmp_count = move_count;
	while (tmp_count > 0)
	{
		buffer[i++] = (tmp_count % 10) + '0';
		tmp_count /= 10;
	}
	if (i == 0) // move_countが0のとき
		buffer[i++] = '0';
	buffer[i] = '\0';
	j = 0;
	i--;
	while (j < i)
	{
		tmp = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = tmp;
		j++;
		i--;
	}
}

static void display_move_count(int move_count)
{
	char	buffer[12];

	int_to_str(move_count, buffer);
	ft_printf("Moved: %s\n", buffer);
}

void player_move(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	dest;

	new_x = game->map.player_x + dx;
	new_y = game->map.player_y + dy;
	dest = game->map.grid[new_y][new_x];
	if (dest == '1')
		return ;
	if (dest == 'E' && game->map.collectibles == 0)
		finish_game(game);
	if (dest == 'C')
	{
		game->map.collectibles--;
		game->map.grid[new_y][new_x] = '0';
	}
	game->move_count++;
	display_move_count(game->move_count);
	draw_cell(game, game->map.player_x, game->map.player_y);
	mlx_put_image_to_window(game->mlx, game->win,
		game->img_p, new_x * TILE_SIZE, new_y * TILE_SIZE);
	game->map.player_x = new_x;
	game->map.player_y = new_y;
}

int on_keypress(int key, t_game *game)
{
	if (key == KEY_ESC)
		finish_game(game);
	else if (key == KEY_W || key == KEY_UP)
		player_move(game, 0, -1);
	else if (key == KEY_S || key == KEY_DOWN)
		player_move(game, 0, 1);
	else if (key == KEY_A || key == KEY_LEFT)
		player_move(game, -1, 0);
	else if (key == KEY_D || key == KEY_RIGHT)
		player_move(game, 1, 0);
	return (0);
}
