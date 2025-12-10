/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:12:25 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/02 20:50:43 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strjoingnl(char *s1, char *s2);
char	*ft_strchrgnl(const char *s, int c);
char	*ft_strdupgnl(const char *str);
void	*ft_memcpygnl(void *dest, const void *src, size_t count);
size_t	ft_strlengnl(const char *str);
char	*update_text(char *text);
int		if_no_text(int fd, int readedbytes, char **text);
char	*if_text(char *line, char **text);
#endif
