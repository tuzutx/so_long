/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:24:49 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/10 16:35:29 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	window(t_game *game, t_map *map)
{
	int	width;
	int	height;

	game_ini;
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
}

void	game_ini(t_game *g)
{
	int	i;
	int	j;

	g->mlx = NULL;
	g->mlx_win = NULL;
	g->w = 0;
	g->h = 0;
	g->current_state = idle;
	g->current_frame = 0;
	g->floor = NULL;
	g->wall = NULL;
	g->c = NULL;
	g->opendoor = NULL;
	g->closeddoor = NULL;
	while (i < 3)
	{
		g->frame_counts[i] = 0;
		while (j < 7)
		{
			g->player_frames[i][j] = 0;
			j++;
		}
		i++;
	}
}

