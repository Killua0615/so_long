/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:43:24 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 12:07:39 by natsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "../minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     collectibles;
    int     exits;
    int     players;
    int     player_x;
    int     player_y;
}   t_map;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    t_map   map;
    int     width;
    int     height;
    void    *img_1;
    void    *img_0;
    void    *img_c;
    void    *img_e;
    void    *img_p;
    int     move_count;
}   t_game;

/* 関数プロトタイプ。map_ad.c 等で使う */
char *get_line_no_newline(int fd);
int count_map(t_game *game, int fd);
int check_map(t_game *game);

// free
void		arr_free(char **arr);
// gnl
char		*gnl_ft_strchr(const char *str, int c);
char		*gnl_ft_strjoin(char *s1, char *s2);
char *gnl_ft_strjoin_alloc(char *s1, size_t l1, char *s2, size_t l2);

// main
void		set_map(t_game *game);
int	collect_map(t_game *game, int width, int height);
int			cheack_map(const char *filename);
void	*get_tile_image(t_game *game, char tile);

// map
char		**read_map(char *file, int lines);
char		*get_next_line(int fd);

//read_and_count
int			read_and_count_lines(int fd, int *count_line);
int			count_lines(char *file);

// map_error
int			walkable_path(char **map, int x, int y, t_map *m);
int			finds_player(t_map *map);

// movements
void		update_current_cell(int x, int y, t_game *game);
void		player_movement(t_game *game, int dx, int dy);
int			handle_keypress(int key, t_game *game);
int			finish_game(t_game *game);
void		print_moved(int move_count);
void		convert_moves_to_string(int move_count, char *buffer);

// utils
char		**ft_arr_dup(char **arr);
int			ft_error(char *message);
int			ft_strlen_line(char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strcmp(const char *s1, const char *s2);
#endif
