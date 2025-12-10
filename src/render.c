/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:06:27 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/10 16:58:11 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	handle_animation(t_game *g, t_map *map)
{
	int	max_frames;

	g->anim_tick++;
	if (g->anim_tick > 500)
	{
		max_frames = g->frame_counts[g->current_state];
		g->current_frame++;
		if (g->current_frame >= max_frames)
			g->current_frame = 0;
		g->anim_tick = 0;
		render_map(g, map); 
    }
    return (0);
}

void	render_player(t_game *g, int i, int j)
{
    void *img_to_draw;
    
    img_to_draw = g->player_frames[g->current_state][g->current_frame];
    mlx_put_image_to_window(g->mlx, g->mlx_win, img_to_draw, j * 32, i * 32);
}

void	render_map(t_game *g, t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < map->rows)
	{
		while (j < map->columns)
		{
			mlx_put_image_to_window(g->mlx, g->mlx_win, g->floor, j * 32, i * 32);
			if (map->grid[i][j] == '1')
				mlx_put_image_to_window(g->mlx, g->mlx_win, g->wall, j * 32, i * 32);
			else if (map->grid[i][j] == 'C')
				mlx_put_image_to_window(g->mlx, g->mlx_win, g->c, j * 32, i * 32);
			else if (map->grid[i][j] == 'E')
				mlx_put_image_to_window(g->mlx, g->mlx_win, g->closeddoor, j * 32, i * 32);
			else if (map->grid[i][j] == 'P')
				render_player(g, i, j);
			j++;
		}
		i++;
	}
}
