/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:54:05 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/03 22:03:28 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*establish_cache(char *cache, int fd)
{
	char	*old_cache;
	int		read_bytes;

	old_cache = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!old_cache)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(cache, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, old_cache, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(old_cache);
			return (NULL);
		}
		old_cache[read_bytes] = '\0';
		cache = ft_strjoin(cache, old_cache);
	}
	free(old_cache);
	return (cache);
}

char	*extract_line(char	*cache)
{
	int		x;
	char	*line;

	x = 0;
	if (!cache[x])
		return (NULL);
	while (cache[x] && cache[x] != '\n')
		x++;
	line = (char *)malloc(sizeof(char) * (x + 2));
	if (!line)
		return (NULL);
	x = 0;
	while (cache[x] && cache[x] != '\n')
	{
		line[x] = cache[x];
		x++;
	}
	if (cache[x] == '\n')
	{
		line[x] = cache[x];
		x++;
	}
	line[x] = '\0';
	return (line);
}

char	*get_next_cache(char	*cache)
{
	int		x;
	int		count;
	char	*next_cache;

	x = 0;
	while (cache[x] && cache[x] != '\n')
		x++;
	if (!cache[x])
	{
		free(cache);
		return (NULL);
	}
	next_cache = (char *)malloc(sizeof(char) * (ft_strlen(cache) - x + 1));
	if (!next_cache)
		return (NULL);
	x++;
	count = 0;
	while (cache[x])
		next_cache[count++] = cache[x++];
	next_cache[count] = '\0';
	free(cache);
	return (next_cache);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*cache;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cache = establish_cache(cache, fd);
	if (!cache)
		return (NULL);
	line = extract_line(cache);
	cache = get_next_cache(cache);
	return (line);
}
