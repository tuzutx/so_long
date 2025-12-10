/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:14:44 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/02 21:12:57 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchrgnl(const char *s, int c)
{
	int				counter;
	char			*str;
	unsigned char	ch;

	if (!s)
		return (NULL);
	str = (char *)s;
	counter = 0;
	ch = (unsigned char)c;
	while (str[counter] != '\0')
	{
		if (str[counter] == ch)
			return (&str[counter]);
		else
			counter++;
	}
	if (str[counter] == c)
		return (&str[counter]);
	return (NULL);
}

void	*ft_memcpygnl(void *dest, const void *src, size_t count)
{
	char	*d;
	char	*s;
	size_t	counter;

	d = (char *)dest;
	s = (char *)src;
	counter = 0;
	if (d == s)
		return (d);
	while (counter < count)
	{
		d[counter] = s[counter];
		counter++;
	}
	return (d);
}

size_t	ft_strlengnl(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
		counter++;
	return (counter);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlengnl(s1) + ft_strlengnl(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdupgnl(const char *str)
{
	char	*copy;
	int		i;

	i = 0;
	copy = (char *)malloc(ft_strlengnl(str) + 1);
	if (!copy)
		return (NULL);
	while (str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = str[i];
	return (copy);
}
