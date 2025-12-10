/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:42:23 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/08 00:01:12 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	printerrormap(t_map *map, t_maptester *tester, char *argv)
{
	map->invalidchar = 0;
	if (opening(map, argv) == 1)
	{
		ft_printf("Error: las dimensiones del mapa no son correctas\n");
		return (1);
	}
	mapload(map);
	if (mapfiller(map, argv) == 1)
	{
		ft_printf("Error: hay caracteres que no se pudieron leer\n");
		return (1);
	}
	if (mapgrid(map, tester) == 1)
		return (1);
	return (0);
}

int	printerrortester(t_map *map, t_maptester *tester)
{
	int	i;

	i = maptester(map, tester);
	if (i == 1)
	{
		ft_printf("Error: El mapa no tiene bordes adecuados\n");
		return (1);
	}
	else if (i == 2)
	{
		ft_printf("Error: Numero erroneo de salidas (E) entradas (P) o coins (C)\n");
		return (1);
	}
	else if (i == 3)
	{
		ft_printf("Error: No hay un camino viable en este mapa\n");
		return (1);
	}
	else if (i == 4)
	{
		ft_printf("Error: No hay un camino viable en este mapa\n");
		return (1);
	}
	else
		return (0);
}

int	errors(char *argv)
{
	t_map		*map;
	t_maptester	*tester;
	int			exit_code;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	tester = (t_maptester *)ft_calloc(1, sizeof(t_maptester));
	if (!map || !tester)
	{
		if (map)
			free(map);
		if (tester)
			free(tester);
		return (1);
	}
	exit_code = 0;
	if (printerrormap(map, tester, argv) == 1)
		exit_code = 1;
	else if (printerrortester(map, tester) == 1)
		exit_code = 1;
	free_map_data(map, tester);
	return (exit_code);
}

int	argcerror(void)
{
	ft_printf("Error: invalid number of argumets\n");
	return (1);
}
