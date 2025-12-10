/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadassets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:05:31 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/10 16:36:45 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int load_frame_sequence(t_game *g, t_player_state state, int count, const char *base_name)
{
	int		i;
	char	*num_str;
	char	*path_tmp;
	char	*path_final;

	i = 0;
	while (i < count)
	{
		num_str = ft_itoa(i + 1);
		path_tmp = ft_strjoin("assets/", base_name);
		path_final = ft_strjoin(path_tmp, num_str);
		free(num_str);
		free(path_tmp); 
		g->player_frames[state][i] = mlx_xpm_file_to_image(g->mlx, path_final, &g->w, &g->h);
		free(path_final); 
		if (g->player_frames[state][i] == NULL)
			return (1);
		if (g->w != 32 && g->h != 32)
			return (2);
		i++;
	}
	g->frame_counts[state] = count;
	return (0);
}

int	load_satatic_image(t_game *g)
{
	g->wall = mlx_xpm_file_to_image(g->mlx, "assets/wall.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (2);
	g->floor = mlx_xpm_file_to_image(g->mlx, "assets/floor.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (2);
	g->c = mlx_xpm_file_to_image(g->mlx, "assets/collection.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (2);
	g->opendoor = mlx_xpm_file_to_image(g->mlx, "assets/door-open.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (2);
	g->closeddoor = mlx_xpm_file_to_image(g->mlx, "assets/door-closed.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (2);
	if (!g->wall || !g->floor || !g->c || !g->opendoor || !g->closeddoor)
        return (1);
	return (0);
}

int	load_assets(t_game *g)
{
	if (load_satatic_image(g) == 1 ||
	load_frame_sequence(g, idle, 3, "character-standing") == 1 ||
	load_frame_sequence(g, walk, 7, "character-walking") == 1 ||
	load_frame_sequence(g, hurt, 4, "character-hurt") == 1)
		return (1);
	if (load_satatic_image(g) == 2 ||
	load_frame_sequence(g, idle, 3, "character-standing") == 2 ||
	load_frame_sequence(g, walk, 7, "character-walking") == 2 ||
	load_frame_sequence(g, hurt, 4, "character-hurt") == 2)
		return (2);
    return (0);
}

