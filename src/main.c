/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:20:30 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/16 10:21:47 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_game	*g;

	g = (t_game *)ft_calloc(1, sizeof(t_game));
	if (argc != 2)
		return (argcerror());
	if (errors(argv[1], g) == 1)
	{
		get_next_line(-1);
		return (1);
	}
	game(g->map, g);
	return (0);
}



