/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadassets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:05:31 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/17 12:12:44 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int load_frame_sequence(t_game *g, t_player_state state, int count, const char *base_name)
{
	int		i;
	char	*num_str;
	char	*path_tmp;
	char	*path_num;
	char	*path_final;

	i = 0;
	while (i < count)
	{
		num_str = ft_itoa(i + 1);
		path_tmp = ft_strjoin("assets/", base_name);
		path_num = ft_strjoin(path_tmp, num_str);
		path_final = ft_strjoin(path_num, ".xpm");
		free(num_str);
		free(path_tmp); 
		free(path_num);
		g->player_frames[state][i] = mlx_xpm_file_to_image(g->mlx, path_final, &g->w, &g->h);
		free(path_final); 
		if (g->player_frames[state][i] == NULL)
			return (1);
		if (g->w != 32 && g->h != 32)
			return (1);
		i++;
	}
	g->frame_counts[state] = count;
	return (0);
}

int	load_satatic_image(t_game *g)
{
	g->wall = mlx_xpm_file_to_image(g->mlx, "assets/wall.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (1);
	g->floor = mlx_xpm_file_to_image(g->mlx, "assets/floor.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (1);
	g->c = mlx_xpm_file_to_image(g->mlx, "assets/collection.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (1);
	g->opendoor = mlx_xpm_file_to_image(g->mlx, "assets/door-open.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (1);
	g->closeddoor = mlx_xpm_file_to_image(g->mlx, "assets/door-closed.xpm", &g->w, &g->h);
	if (g->w != 32 && g->h != 32)
			return (1);
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
    return (0);
}
