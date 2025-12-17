/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:37:43 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/17 13:24:30 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	get_map_dimensions(t_map *map)
{
	char	*line;

	map->rows = 0;
	line = get_next_line(map->fd);
	while (line != NULL)
	{
		map->rows++;
		if (map->rows == 1)
		{
			map->columns = ft_strlen(line);
			if (map->columns > 0 && line[map->columns - 1] == '\n')
				map->columns--;
		}
		free(line);
	}
	close(map->fd);
	if (map->rows == 0 || map->columns == 0 || map->rows == map->columns)
		return (1);
	return (0);
}

// This function opens and reads the rows and columns
int	opening(t_map *map, char *argv)
{
	map->fd = open(argv, O_RDONLY);
	if (map->fd == -1)
	{
		perror("Error al abrir el archivo\n");
		return (1);
	}
	if (get_map_dimensions(map) == 1)
	{
		if (map->fd != -1)
			close(map->fd);
		return (get_map_dimensions(map));
	}
	if (mapdimensions(map, argv) == 1)
		return (1);
	return (0);
}

//This function books space for the map
void	mapload(t_map *map)
{
	int	rows;

	map->grid = (char **)malloc(sizeof(char *) * (map->rows + 1));
	if (map->grid == NULL)
	{
		perror("Error de malloc para las filas");
		return ;
	}
	rows = 0;
	while (rows < map->rows)
	{
		map->grid[rows] = (char *)malloc(sizeof(char) * (map->columns + 1));
		if (map->grid[rows] == NULL)
		{
			while (rows > 0)
				free(map->grid[--rows]);
			free(map->grid);
			perror("Error de malloc para la línea");
			return ;
		}
		rows ++;
	}
	map->grid[map->rows] = NULL;
	return ;
}

//This function checks the valid characters for the map
void	map_loop(t_map *map)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	line = get_next_line(map->fd2);
	while (line != NULL)
	{
		j = 0;
		while (j < map->columns && !map->invalidchar)
		{
			if ((j != '1') && (j != '0') && (j != 'P')
				&& (j != 'C') && (j != 'E') && (j != '\0'))
			{
				map->invalidchar++;
				return ;
			}
			map->grid[i][j] = line[j];
			j++;
		}
		map->grid[i][j] = '\0';
		free(line);
		i++;
	}
	return ;
}

//This function stuffed the map
int	mapfiller(t_map *map, char *argv)
{
	map->fd2 = open(argv, O_RDONLY);
	if (map->fd2 == -1)
	{
		perror("Error al reabrir el archivo para el guardado");
		return (2);
	}
	map_loop(map);
	close(map->fd2);
	return (map->invalidchar);
}
