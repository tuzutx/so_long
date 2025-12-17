/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:21:36 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/17 12:54:45 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	if_no_text(int fd, int readedbytes, char **text)
{
	char		*temptext;

	temptext = malloc(BUFFER_SIZE + 1);
	if (!temptext)
		return (-1);
	while (ft_strchrgnl(*text, '\n') == NULL && readedbytes > 0)
	{
		readedbytes = read(fd, temptext, BUFFER_SIZE);
		if (readedbytes == -1)
		{
			if (*text)
			{
				free(*text);
				*text = NULL;
			}
			free(temptext);
			return (-1);
		}
		temptext[readedbytes] = '\0';
		*text = ft_strjoingnl(*text, temptext);
		if (!*text)
			return (-1);
	}
	free(temptext);
	return (1);
}

char	*extract_line(const char *text)
{
	int		i;
	char	*line;

	if (!text || text[0] == '\0')
		return (NULL);
	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (text[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpygnl(line, text, i);
	line[i] = '\0';
	return (line);
}

char	*if_text(char *line, char **text)
{
	line = extract_line(*text);
	*text = update_text(*text);
	return (line);
}

char	*update_text(char *text)
{
	char	*rest;
	char	*new_text;

	rest = ft_strchrgnl(text, '\n');
	if (!rest)
	{
		free(text);
		return (NULL);
	}
	rest++;
	new_text = ft_strdupgnl(rest);
	free(text);
	return (new_text);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			readedbytes;
	int			check;
	static char	*text;

	if (fd < 0)
	{
		if (text)
		{
			free(text);
			text = NULL;
		}
		return (NULL);
	}
	line = NULL;
	readedbytes = 1;
	if (text && ft_strchrgnl(text, '\n') != NULL)
		return (line = if_text(line, &text));
	else
		check = if_no_text(fd, readedbytes, &text);
	if (check == -1)
		return (NULL);
	else
		return (line = if_text(line, &text));
}
