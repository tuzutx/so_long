/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:20:30 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/07 23:50:47 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (argcerror());
	if (errors(argv[1]) == 1)
	{
		get_next_line(-1);
		return (1);
	}
	ft_printf("TODO HA IDO BIEN!!");
	return (0);
}



