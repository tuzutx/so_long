/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:50:41 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/17 11:56:18 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map_data(t_map *map, t_maptester *tester)
{
    int i = 0;
    if (map && map->grid)
    {
        while (i < map->rows)
            free(map->grid[i++]);
        free(map->grid);
    }
    i = 0;
    if (tester && tester->visited)
    {
        while (i < map->rows)
            free(tester->visited[i++]);
        free(tester->visited);
    }
    free(map);
    free(tester);
}
void	clean_static_image(t_game *g)
{
	if (g->wall)
		mlx_destroy_image(g->mlx, g->wall);
	if (g->floor)
		mlx_destroy_image(g->mlx, g->floor);
	if (g->c)
		mlx_destroy_image(g->mlx, g->c);
	if (g->closeddoor)
		mlx_destroy_image(g->mlx, g->closeddoor);
	if (g->opendoor)
		mlx_destroy_image(g->mlx, g->opendoor);
	return ;
}

void	clean_image(t_game *g)
{
	int	i;

	clean_static_image(g);
	i = 0;
	while (g->player_frames[idle][i])
	{
		mlx_destroy_image(g->mlx, g->player_frames[idle][i]);
		g->player_frames[idle][i] = NULL;
		i++;
	}
	i = 0;
	while (g->player_frames[walk][i])
	{
		mlx_destroy_image(g->mlx, g->player_frames[walk][i]);
		g->player_frames[walk][i] = NULL;
		i++;
	}
	i = 0;
	while (g->player_frames[hurt][i])
	{
		mlx_destroy_image(g->mlx, g->player_frames[hurt][i]);
		g->player_frames[hurt][i] = NULL;
		i++;
	}
	return ;
}

int	clean_exit(t_game *g)
{
	t_map		*map;
	t_maptester	*tester;

	map = g->map;
	tester = g->tester;
	clean_image(g);
	if (g->mlx_win)
		mlx_destroy_window(g->mlx, g->mlx_win);
	if (g->mlx)
		mlx_destroy_display(g->mlx);
	free_map_data(map, tester);
	free(g);
	exit(0);
	return (0);
}
