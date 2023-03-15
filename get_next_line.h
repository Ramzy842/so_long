/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 04:33:31 by rchahban          #+#    #+#             */
/*   Updated: 2022/11/25 18:02:58 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char			*get_next_line(int fd);
char			*get_next_cache(char	*cache);
char			*extract_line(char	*cache);
char			*establish_cache(char *cache, int fd);
size_t			ft_strlen(char *str);
char			*ft_strchr(char *s, int c);
char			*ft_strjoin(char *s1, char *s2);

#endif