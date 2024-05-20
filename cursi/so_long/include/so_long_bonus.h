/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:02:18 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 19:42:09 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "MLX42.h"
# include "ft_printf.h"
# include "push_swap.h"

# define WIDTH 48
# define HEIGHT 48
# define ANIMATION_TIME 60
# define ACTIONS 7
# define PLAYER_SPRITES 4
# define COINS_TYPES 7
# define ENEMIES_TYPES 4

typedef enum player_action
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STOP,
	FIGHT,
	DIED
}					t_player_action;

typedef struct s_map
{
	char			**value;
	char			*name;
	int				height;
	int				width;
	int				capacity;
}					t_map;

typedef struct s_player
{
	mlx_texture_t	*texture[ACTIONS][PLAYER_SPRITES];
	mlx_image_t		*sprites[ACTIONS][PLAYER_SPRITES];
	mlx_image_t		*img;
	int				current_sprite;
	int				x;
	int				y;
	int				direction;
	int				time;
	bool			is_alive;
}					t_player;

typedef struct s_background
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;
}					t_background;

typedef struct s_wall
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;
}					t_wall;

typedef struct s_coin
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;
	int				x;
	int				y;
}					t_coin;

typedef struct s_exit
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;
}					t_exit;

typedef struct s_enemy
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;
	int				x;
	int				y;
}					t_enemy;

typedef struct s_game
{
	t_map			map;
	t_player		player;
	t_background	bg;
	t_wall			wall[2];
	t_coin			coin[100];
	t_enemy			enemy[100];
	t_exit			exit;
	int				total_coins;
	int				collected_coins;
	int				total_enemies;
	int				moves;
	bool			win;
	mlx_t			*mlx;
}					t_game;
//	map functions
void				check_extension(t_map *map);
void				print_map(t_map *map);
void				read_map(t_map *map, char *path);
//	utils functions
void				animation(void *param);
void				ft_error_map(t_map *map, const char *message);
void				end_game(t_game *game);
//	validation functions
void				validate_map(t_map *map);
//	path functions
void				validate_path(t_game *game);
//	game functions
void				init_parameters(t_game *game);
void				key_press_event(mlx_key_data_t keycode, void *param);
void				load_game(t_game *game);
//	player functions
void				move_player(t_game *game, int x, int y,
						t_player_action action);
void				load_player_sprites(t_game *game);
void				delete_player(t_game *game);
//	move functions
void				update_direction(t_game *game, t_player_action action);
void				perform_fight_action(t_game *game, int *x, int *y);
bool				handle_map_interaction(t_game *game, int x, int y,
						t_player_action action);
void				update_player_position(t_game *game, int x, int y,
						t_player_action act);
void				check_game_status(t_game *game, t_player_action action);
//	coin functions
void				load_coins(t_game *game);
void				delete_coin(t_game *game, int x, int y);
void				delete_all_coins(t_game *game);
//	enemy functions
void				load_enemies(t_game *game);
void				delete_enemy(t_game *game, int x, int y);
void				delete_all_enemies(t_game *game);
#endif