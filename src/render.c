/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:06:27 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/17 13:37:10 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	starting_point(t_map *map, t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			if (map->grid[i][j] == 'P')
			{
				g->player_x = j;
				g->player_y = i;
				map->grid[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	render_player(t_game *g)
{
	void	*img_to_draw;

	img_to_draw = g->player_frames[g->current_state][g->current_frame];
	mlx_put_image_to_window(g->mlx, g->mlx_win,
		img_to_draw, g->player_x * 32, g->player_y * 32);
}

void	render_map(t_game *g, t_map *map, t_maptester *coins)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			if (i == g->player_y && g->player_x == j)
				render_player(g);
			else if (map->grid[i][j] == '0')
				mlx_put_image_to_window(g->mlx, g->mlx_win,
					g->floor, j * 32, i * 32);
			else if (map->grid[i][j] == '1')
				mlx_put_image_to_window(g->mlx, g->mlx_win,
					g->wall, j * 32, i * 32);
			else if (map->grid[i][j] == 'C')
				mlx_put_image_to_window(g->mlx, g->mlx_win,
					g->c, j * 32, i * 32);
			else if (map->grid[i][j] == 'E' 
				&& coins->coinsfound != g->catchcoins)
				mlx_put_image_to_window(g->mlx, g->mlx_win,
					g->closeddoor, j * 32, i * 32);
			else if (map->grid[i][j] == 'E' && coins->coinsfound == g->catchcoins)
				mlx_put_image_to_window(g->mlx, g->mlx_win,
					g->opendoor, j * 32, i * 32);
			j++;
		}
		i++;
	}
}

int	handle_animation(t_game *g)
{
	t_map		*map;
	t_maptester	*tester;
	int			max_frames;

	map = g->map;
	tester = g->tester;
	g->anim_tick++;
	if (g->anim_tick > 1500)
	{
		max_frames = g->frame_counts[g->current_state];
		g->current_frame++;
		if (g->current_frame >= max_frames)
			g->current_frame = 0;
		g->anim_tick = 0;
		if (g->current_state == walk)
			g->last_move_frame++;
		if (g->last_move_frame > g->frame_counts[walk])
		{
			g->current_state = idle;
			g->current_frame = 0;
			g->last_move_frame = 0;
		}
		render_map(g, map, tester); 
    }
    return (0);
}
