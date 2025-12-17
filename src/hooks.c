/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:30:24 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/15 18:51:33 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	key_press(int keycode, t_game *g)
{
	t_map		*map;
	t_maptester	*tester;

	map = g->map;
	tester = g->tester;
	if (keycode == 119)
		moveup(g, map, tester);
	else if (keycode == 97)
		moveleft(g, map, tester);
	else if (keycode == 115)
		movedown(g, map, tester);
	else if (keycode == 100)
		moveright(g, map, tester);
	else if (keycode == 65307)
		clean_exit(g);
	return (0);
}

void	init_hooks(t_game *g)
{
	mlx_key_hook(g->mlx_win, &key_press, g);
	mlx_hook(g->mlx_win, 17, 0, &clean_exit, g);
	mlx_loop_hook(g->mlx, &handle_animation, g);
}
