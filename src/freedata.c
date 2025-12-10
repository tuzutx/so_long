/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:50:41 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/04 10:51:21 by nolaeche         ###   ########.fr       */
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
