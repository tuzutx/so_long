/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:24:49 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/16 10:32:23 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	game_ini(t_game *g, int *i, int *j)
{
	g->mlx = NULL;
	g->mlx_win = NULL;
	g->w = 0;
	g->h = 0;
	g->catchcoins = 0;
	g->movemnts = 0;
	g->current_state = idle;
	g->current_frame = 0;
	g->floor = NULL;
	g->wall = NULL;
	g->c = NULL;
	g->opendoor = NULL;
	g->closeddoor = NULL;
	while (*i < 3)
	{
		g->frame_counts[*i] = 0;
		while (*j < 7)
		{
			g->player_frames[*i][*j] = 0;
			(*j)++;
		}
		(*i)++;
	}
	return ;
}

int	window(t_game *game, t_map *map)
{
	int	width;
	int	height;
	int	i;
	int	j;

	i = 0;
	j = 0;
	game_ini(game, &i, &j);
	width = 32 * map->columns;
	height = 32 * map->rows;
	if (width > 1920 || height > 1080)
		return (1);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (2);
	game->mlx_win = mlx_new_window(game->mlx, width, height, "so_long");
	if (game->mlx_win == NULL)
		return (3);
	return (0);
}

/* int	game_errors(t_map *map, t_game *g)
{
	if (window(g, map) == 1)
	{
		ft_printf("Error: El juego no soporta mapas tan grandes");
		return (1);
	}
	else if (window(g, map) == 2)
	{
		ft_printf("Erorr: El iniciador del gráfico falló");
		return (1);
	}
	if (load_assets(g) == 1)
	{
		ft_printf("Error: las imágenes no pudeiron cargarse");
		return (1);
	}
	else if (load_assets(g) == 2)
	{
		ft_printf("Error: las imágenes no son de 32x32");
		return (1);
	}
	return (0);
} */

void	game(t_map *map, t_game *g)
{
	if (!map || !g || !g->mlx_win)
		return ;
	starting_point(map, g);
	render_map(g, map, g->tester);
	init_hooks(g);
	mlx_loop(g->mlx);
}

