/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maptester.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:29:39 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/17 13:30:50 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	resetvisited(t_map *map, t_maptester *tester)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			tester->visited[i][j] = '0';
			j++;
		}
		i++;
	}
	return ;
}

int	maptester(t_map *map, t_maptester *tester)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	tester->coins = 0;
	tester->start = 0;
	tester->end = 0;
	if (mapborders(map) == 1)
		return (1);
	colectorssnum(map, tester, &i, &j);
	if (tester->start != 1 || tester->end != 1 || tester->coins == 0)
		return (2);
	tester->coinsfound = 0;
	checkcoins(map, tester, i, j);
	if (tester->coinsfound != tester->coins)
		return (3);
	resetvisited(map, tester);
	tester->exitfound = 0;
	checkexit(map, tester, i, j);
	if (tester->exitfound != 1)
		return (4);
	return (0);
}

int	mapdimensions(t_map *map, char *argv)
{
	int		fd;
	char	*line;
	int		rows;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo\n");
		return (1);
	}
	rows = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		rows++;
		if ((rows < map->rows && map->columns != ((int)ft_strlen(line) - 1))
			|| (rows == map->rows && map->columns != (int)ft_strlen(line)))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
	}
	return (0);
}
