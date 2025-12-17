/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:15:19 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/17 13:34:41 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	moveup(t_game *g, t_map *map, t_maptester *totalcoins)
{
	if (map->grid[g->player_y - 1][g->player_x] == '1')
		return ;
	g->last_move_frame = 0;
	g->current_state = walk;
	g->player_y--;
	g->movemnts++;
	ft_printf("Movimientos: %d\n", g->movemnts);
	if (map->grid[g->player_y][g->player_x] == 'C')
	{
		g->catchcoins++;
		map->grid[g->player_y][g->player_x] = '0';
	}
	else if (map->grid[g->player_y][g->player_x] == 'E'
		&& g->catchcoins == totalcoins->coinsfound)
	{
		render_map(g, map, totalcoins);
		clean_exit(g);
	}
	render_map(g, map, totalcoins);
	return ;
}

void	movedown(t_game *g, t_map *map, t_maptester *totalcoins)
{
	if (map->grid[g->player_y + 1][g->player_x] == '1')
		return ;
	g->last_move_frame = 0;
	g->current_state = walk;
	g->player_y++;
	g->movemnts++;
	ft_printf("Movimientos: %d\n", g->movemnts);
	if (map->grid[g->player_y][g->player_x] == 'C')
	{
		g->catchcoins++;
		map->grid[g->player_y][g->player_x] = '0';
	}
	else if (map->grid[g->player_y][g->player_x] == 'E'
		&& g->catchcoins == totalcoins->coinsfound)
	{
		render_map(g, map, totalcoins);
		clean_exit(g);
	}
	render_map(g, map, totalcoins);
	return ;
}

void	moveleft(t_game *g, t_map *map, t_maptester *totalcoins)
{
	if (map->grid[g->player_y][g->player_x - 1] == '1')
		return ;
	g->last_move_frame = 0;
	g->current_state = walk;
	g->player_x--;
	g->movemnts++;
	ft_printf("Movimientos: %d\n", g->movemnts);
	if (map->grid[g->player_y][g->player_x] == 'C')
	{
		g->catchcoins++;
		map->grid[g->player_y][g->player_x] = '0';
	}
	else if (map->grid[g->player_y][g->player_x] == 'E'
		&& g->catchcoins == totalcoins->coinsfound)
	{
		render_map(g, map, totalcoins);
		clean_exit(g);
	}
	render_map(g, map, totalcoins);
	return ;
}

void	moveright(t_game *g, t_map *map, t_maptester *totalcoins)
{
	if (map->grid[g->player_y][g->player_x + 1] == '1')
		return ;
	g->last_move_frame = 0;
	g->current_state = walk;
	g->player_x++;
	g->movemnts++;
	ft_printf("Movimientos: %d\n", g->movemnts);
	if (map->grid[g->player_y][g->player_x] == 'C')
	{
		g->catchcoins++;
		map->grid[g->player_y][g->player_x] = '0';
	}
	else if (map->grid[g->player_y][g->player_x] == 'E'
		&& g->catchcoins == totalcoins->coinsfound)
	{
		render_map(g, map, totalcoins);
		clean_exit(g);
	}
	render_map(g, map, totalcoins);
	return ;
}
