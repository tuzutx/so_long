/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:42:23 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/17 13:02:10 by nolaeche         ###   ########.fr       */
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
		ft_printf("Error: Numero erroneo de salidas (E)"
			"entradas (P) o coins (C)\n");
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
	return (0);
}

int	print_gameerrors(t_game *g)
{
	int	res;

	res = window(g, g->map);
	if (res == 1)
	{
		ft_printf("Error: El mapa es muy grande\n");
		clean_exit(g);
	}
	else if (res == 2)
	{
		ft_printf("Error: Inicialización de los gráficos falló\n");
		clean_exit(g);
	}
	else if (res == 3)
	{
		ft_printf("Error: No se pudeo abrir la ventana\n");
		clean_exit(g);
	}
	res = load_assets(g);
	if (res == 1)
	{
		ft_printf("Error: Error al cargar las imágenes\n");
		clean_exit(g);
	}
	return (0);
}

int	errors(char *argv, t_game *g)
{
	t_map		*map;
	t_maptester	*tester;

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
	if (printerrormap(map, tester, argv) == 1
		|| printerrortester(map, tester) == 1)
	{
		free_map_data(map, tester);
		return (1);
	}
	g->map = map;
	g->tester = tester;
	if (print_gameerrors(g) == 1)
		return (1);
	return (0);
}

int	argcerror(void)
{
	ft_printf("Error: invalid number of argumets\n");
	return (1);
}
