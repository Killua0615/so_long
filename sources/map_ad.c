#include "../so_long.h"

int count_map(t_game *game, int fd)
{
    int   i;
    int   max_lines;
    char  *line;

    max_lines = 10000; /* 仮の大きな数 */
    /* 2次元配列を、行数として仮に10001個分確保 */
    game->map.grid = (char **)malloc(sizeof(char *) * (max_lines + 1));
    if (!game->map.grid)
    {
        ft_error("Error\nFailed to allocate memory for grid");
        return (1);
    }

    i = 0;
    game->map.height = 0;
    game->map.width = 0;

    /* 最初の行を読み込み */
    line = get_next_line(fd);

    /* ファイルが空(1行も読めない)ならエラー */
    if (!line)
    {
        ft_error("Error\nFile is empty!");
        return (1);
    }

    /* 行がある限りループ */
    while (line)
    {
        /* 行の長さを調べる */
        int len = 0;
        while (line[len])
            len++;

        /* 末尾の改行(\n)を削除 */
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
            len--;
        }

        /* 1行目でwidthを決定 */
        if (i == 0)
        {
            game->map.width = len; /* そのまま幅として保存 */
            if (len == 0)
            {
                free(line);
                ft_error("Error\nMap's first line is empty");
                return (1);
            }
        }
        else
        {
            /* 2行目以降は 幅が合うかチェック */
            if (len != game->map.width)
            {
                free(line);
                ft_error("Error\nMap is not rectangle");
                return (1);
            }
        }

        /* 配列に行を格納 */
        game->map.grid[i] = line;
        i++;
        game->map.height++;

        /* 次の行を読む */
        line = get_next_line(fd);
    }

    /* 終端NULL */
    game->map.grid[i] = NULL;
    return (0);
}

int check_map(t_game *game)
{
    int i = 0, j;
    // P, E, C の個数を個別に数える
    int countP = 0;
    int countE = 0;
    int countC = 0;

    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            char c = game->map.grid[i][j];

            // 1) 不正文字チェック
            if (!ft_strchr("01CEP", c))
            {
                ft_error("Error\nInvalid map letter");
                return (1);
            }
            // 2) 外壁チェック
            if ((i == 0 || i == game->map.height - 1 || j == 0 || j == game->map.width - 1)
                && c != '1')
            {
                ft_error("Error\nMap isn't be closed by walls(1)");
                return (1);
            }
            // 3) 個数カウント
            if (c == 'P')
                countP++;
            else if (c == 'E')
                countE++;
            else if (c == 'C')
                countC++;
            
            j++;
        }
        i++;
    }

    // 4) P, E, C の個数が適正か？ 
    //    - P==1, E==1, C>=1 でなければエラー
    if (countP != 1)
    {
        ft_error("Error\nPlayer(P) must be exactly 1");
        return (1);
    }
    if (countE != 1)
    {
        ft_error("Error\nExit(E) must be exactly 1");
        return (1);
    }
    if (countC < 1)
    {
        ft_error("Error\nNo collectibles(C) found");
        return (1);
    }

    // 5) 残りのロジック: P から (C+E) に到達できるか
    //    - ここで “map->collectibles = countC; map->exits = 1” などにセット
    game->map.collectibles = countC;
    game->map.exits = 1;

    // P から全Cと E を踏めるかwalkable_pathチェック
    // finds_player が walkable_path(...) して、見つけたC+E 個数を返す
    int result = finds_player(&game->map);
    int needed = countC + 1; // 1つのE + countC個
    if (result < needed)
    {
        ft_error("Error\nNo valid path from P to all C and E");
        return (1);
    }
    return (0); // OK
}
