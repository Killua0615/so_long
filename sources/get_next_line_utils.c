/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:44:57 by nateshim          #+#    #+#             */
/*   Updated: 2025/02/08 18:46:19 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*gnl_ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*gnl_ft_strdup(const char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc((ft_strlen(str) + 1));
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static void	copy_strings(char *dest, const char *src, size_t *index)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[*index] = src[i];
		(*index)++;
		i++;
	}
}

char	*gnl_ft_strjoin_alloc(char *s1, size_t l1, char *s2, size_t l2)
{
	size_t	i;
	char	*j;

	i = 0;
	j = malloc(l1 + l2 + 1);
	if (!j)
	{
		free(s1);
		return (NULL);
	}
	copy_strings(j, s1, &i);
	copy_strings(j, s2, &i);
	j[i] = '\0';
	free(s1);
	return (j);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	if (!s1)
	{
		s1 = gnl_ft_strdup("");
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	return (gnl_ft_strjoin_alloc(s1, len1, s2, len2));
}
