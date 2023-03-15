/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:54:05 by rchahban          #+#    #+#             */
/*   Updated: 2022/11/25 23:42:12 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	x;

	x = 0;
	if (!str)
		return (0);
	while (str[x] != '\0')
		x++;
	return (x);
}

char	*ft_strchr(char *s, int c)
{
	int	x;

	x = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[x] != '\0')
	{
		if (s[x] == (char) c)
			return ((char *)&s[x]);
		x++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	x;
	size_t	count;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	x = -1;
	count = 0;
	if (s1)
		while (s1[++x] != '\0')
			str[x] = s1[x];
	while (s2[count] != '\0')
		str[x++] = s2[count++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}
