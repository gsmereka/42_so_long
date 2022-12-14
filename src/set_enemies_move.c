/* ************************************************************************** */
/*						                                                    */
/*                                                        :::      ::::::::   */
/*   set_enemies_move_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 01:58:36 by gsmereka          #+#    #+#             */
/*   Updated: 2022/10/16 16:31:31 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

static void	select_enemies(t_data *game);
static void	move_enemy(char *pos, t_data *game);

void	set_enemies_move(t_data *game)
{
	clock_t			now;
	static long int	save;

	now = clock();
	if (now - save > 150000)
	{
		save = now;
		select_enemies(game);
	}
}

static void	select_enemies(t_data *game)
{
	int	i;

	i = game->map->objects->n_enemies - 1;
	while (i >= 0)
	{
		move_enemy(game->enemy->pos[i], game);
		i--;
	}
}

static void	move_enemy(char *pos, t_data *game)
{
	int	x;
	int	y;
	int	dir;

	x = pos[0] - '0';
	y = pos[1] - '0';
	dir = pos[2] - '0';
	if (dir == 0)
		dir = -1;
	if (game->map->grid[y + dir][x] == '0')
	{
		pos[1] = y + dir + '0';
		game->map->grid[y][x] = '0';
		game->map->grid[y + dir][x] = 'X';
	}
	else if (game->map->grid[y + dir][x] == 'P')
		set_shutdown(1, game, "YOU DIED\n");
	else
	{
		if (dir > 0)
			pos[2] = 0 + '0';
		else
			pos[2] = 1 + '0';
	}
}
