/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:45:04 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/07 23:14:33 by natsumi          ###   ########.fr       */
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
			ft_free(new_arr);
			return (NULL);
		}
		j++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}
