/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:09:00 by nolaeche          #+#    #+#             */
/*   Updated: 2025/12/10 16:58:07 by nolaeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct	s_map
{
	int		rows;
	int 	columns;
	int		fd;
	int		fd2;
	int		invalidchar;
	char	**grid;
}			t_map;

typedef struct s_maptester
{
	int		start;
	int		end;
	int		coins;
	int		coinsfound;
	int		exitfound;
	char	**visited;
}			t_maptester;

typedef enum e_player_state
{
	idle,
	walk,
	hurt,
	state_count
}	t_player_state;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
	int				w;
	int				h;
	//player animation
	t_player_state	current_state;
	int				current_frame;
	int				anim_tick;
	int				frame_counts[state_count];
	void			*player_frames[state_count][7];
	//static image
	void			*floor;
	void			*wall;
	void			*c;
	void			*opendoor;
	void			*closeddoor;
}					t_game;

#include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h> 
# include "../src/minilibx-linux/mlx.h"
# include "../src/getnextline/get_next_line.h"
# include "../src/libft/libft.h"
# include "../src/printf/include/ft_printf.h"

//map.c
int		opening(t_map *map, char *argv);
void	mapload(t_map *map);
int		mapfiller(t_map *map, char *argv);
void	checkchar(t_map *map, char j);
int		get_map_dimensions(t_map *map);
//maptester.c
int		maptester(t_map *map, t_maptester *tester);
void	resetvisited(t_map *map,t_maptester *tester);
int		mapdimensions(t_map *map, char *argv);
//maptesteraux.c
int		mapborders(t_map *map);
int		colectorssnum(t_map *map, t_maptester *tester, int *n, int *m);
int		mapgrid(t_map *map, t_maptester *tester);
void	checkexit(t_map *map, t_maptester *maptester, int i, int j);
void	checkcoins(t_map *map, t_maptester *maptester, int i, int j);
//errors.c
int		printerrormap(t_map *map, t_maptester *tester, char *argv);
int		printerrortester(t_map *map, t_maptester *tester);
int		errors(char *argv);
int		argcerror(void);
//freedata.c
void	free_map_data(t_map *map, t_maptester *tester);
//game.c
int		window(t_game *game, t_map *map);
void	game_ini(t_game *g);
//loadassets.c
int 	load_frame_sequence(t_game *g, t_player_state state, int count, const char *base_name);
int		load_satatic_image(t_game *g);
int		load_assets(t_game *g);
//render.c
int		handle_animation(t_game *g, t_map *map);
void	render_player(t_game *g, int i, int j);
void	render_map(t_game *g, t_map *map);



#endif
