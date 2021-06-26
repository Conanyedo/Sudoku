/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:05:56 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/26 11:23:05 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sudoku.h"

int		if_solved(t_sudo *sudo)
{
	int		x;
	int		y;

	y = -1;
	while (++y < 9)
	{
		x = -1;
		while (++x < 9)
		{
			if (sudo->grid[y][x] != sudo->solved[y][x])
				return (0);
		}
	}
	return (1);
}

void	err_msg(t_sudo *sudo, char *msg)
{
	write(1, "\033[1A\r\033[K", 8);
	ft_putstr_fd("\e[0;31m", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\e[0m", 1);
	sleep(2);
	sudo->grids = 24;
	write(1, "\r\033[K", 8);
}

int		check_if_break(t_sudo *sudo, int x, int y, int num)
{
	int		cell;

	cell = which_cell(x, y);
	if (((sudo->row[y] >> (num - 1)) & 1) || ((sudo->col[x] >> (num - 1)) & 1)
	|| ((sudo->cell[cell] >> (num - 1)) & 1))
		return (1);
	sudo->row[y] = (1 << (num - 1)) | sudo->row[y];
	sudo->col[x] = (1 << (num - 1)) | sudo->col[x];
	sudo->cell[cell] = (1 << (num - 1)) | sudo->cell[cell];
	return (0);
}

int		which_cell(int x, int y)
{
	int		cell;

	cell = 0;
	if (!(y / 3))
		cell = (x / 3);
	else if ((y / 3) == 1)
		cell = (x / 3) + 3;
	else if ((y / 3) == 2)
		cell = (x / 3) + 6;
	return (cell);
}

void	fill_grid(t_sudo *sudo, int grid[9][9])
{
	int		x;
	int		y;

	y = -1;
	while (++y < 9)
	{
		x = -1;
		while (++x < 9)
			sudo->solved[y][x] = grid[y][x];
	}
	y = -1;
	while (++y < 9)
	{
		x = -1;
		while (++x < 9)
			sudo->grid[y][x] = grid[y][x];
	}
}

void	prev(int *x, int *y)
{
	if (!*x && *y)
	{
		(*y)--;
		*x = 8;
	}
	else
		(*x)--;
}
