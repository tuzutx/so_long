/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maptesteraux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:34:42 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/03 19:54:00 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	mapborders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->columns)
	{
		if (map->grid[0][i] != '1') 
			return (1); 
		if (map->grid[map->rows - 1][i] != '1') 
			return (1);
		i++;
	}
	i = 1;
	while (i < map->rows - 1)
	{
		if (map->grid[i][0] != '1') 
			return (1);
		if (map->grid[i][map->columns - 1] != '1') 
			return (1);
		i++;
    }
	return (0);
}

int	colectorssnum(t_map *map, t_maptester *tester, int *n, int *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			if (map->grid[i][j] == 'C')
				tester->coins++;
			else if (map->grid[i][j] == 'E')
				tester->end++;
			else if (map->grid[i][j] == 'P')
			{
				*n = i;
				*m = j;
				tester->start++;
			}
			j++;
		}
		i++;
	}
	if (tester->start != 1 || tester->end != 1 || tester->coins == 0)
		return (1);
	return (0);
}

int	mapgrid(t_map *map, t_maptester *tester)
{
	int	rows;

	tester->visited = (char **)ft_calloc((map->rows + 1), sizeof(char *));
    if (tester->visited == NULL)
    {
        perror("Error de malloc para las filas en visited");
        return (1);
    }
	rows = 0;
	while (rows < map->rows)
	{
		tester->visited[rows] = (char*)ft_calloc((map->columns + 1), sizeof(char));
		if (tester->visited[rows] == NULL)
		{
			while (rows > 0)
                free(tester->visited[--rows]);
            free(tester->visited);
			perror("Error de malloc para la línea en visited");
			return (1);
		}
		rows ++;
	}
	tester->visited[map->rows] = NULL;
	return (0);
}

void	checkcoins(t_map *map, t_maptester *maptester, int i, int j)
{
	if (i < 0 || j < 0 || i >= map->rows || j >= map->columns ||
		maptester->visited[i][j] == 'V' || map->grid[i][j] == '1' ||
		map->grid[i][j] == 'E')
		return ;
	maptester->visited[i][j] = 'V';
	if (map->grid[i][j] == 'C')
		maptester->coinsfound++;
	checkcoins(map, maptester, i + 1, j);
	checkcoins(map, maptester, i - 1, j);
	checkcoins(map, maptester, i, j + 1);
	checkcoins(map, maptester, i, j - 1);
	return ;
}

void	checkexit(t_map *map, t_maptester *maptester, int i, int j)
{
	if (i < 0 || j < 0 || i >= map->rows || j >= map->columns ||
		maptester->visited[i][j] == 'V' || map->grid[i][j] == '1')
		return ;
	maptester->visited[i][j] = 'V';
	if (map->grid[i][j] == 'E')
		maptester->exitfound = 1;
	checkexit(map, maptester, i + 1, j);
	checkexit(map, maptester, i - 1, j);
	checkexit(map, maptester, i, j + 1);
	checkexit(map, maptester, i, j - 1);
	return ;
}
