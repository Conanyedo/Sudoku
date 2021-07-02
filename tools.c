/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:05:56 by ybouddou          #+#    #+#             */
/*   Updated: 2021/07/02 14:55:26 by ybouddou         ###   ########.fr       */
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

int		set_bits(int cell)
{
	int		i;
	int		c;

	c = 0;
	i = -1;
	while (++i < 9)
	{
		if ((1 << i) & cell)
			c++;
	}
	return (c);
}

int		check_shuffled(t_sudo *sudo, int x, int with)
{
	int		cell;

	cell = which_cell(x, 0) + which_cell(with, 0);
	if (((sudo->cell_shuffle[cell] >> (cell)) & 1) || ((sudo->shuffled[x] >> (x)) & 1))
		return (1);
	sudo->shuffled[x] = (1 << x) | sudo->shuffled[x];
	// sudo->shuffled[with] = (1 << with) | sudo->shuffled[with];
	sudo->cell_shuffle[cell] = (1 << (cell)) | sudo->cell_shuffle[cell];
	return (0);
}

int		start_subgrid(int x)
{
	int		start;

	start = x / 3;
	if (start == 1)
		start += 2;
	else if (start == 2)
		start += 4;
	return (start);
}

void	shuffle(t_sudo *sudo)
{
	int		i;
	int		x;
	int		y;
	int		with;
	int		tmp;
	int		y_end;
	int		x_end;

	srand(time(0));
	i = rand() % (3 - 2 + 1) + 2;
	// printf("i : %d\n\n", i);
	while (i--)
	{
		do
		{
			x = rand() % 8;
			with = x + 3;
			with = with > 8 ? (with - 9) : with;
		} while (check_shuffled(sudo, x, with));
		// printf("x : %d | with : %d\n", x, with);
		y = -1;
		while (++y < 9)
		{
			tmp = sudo->solved[y][x];
			sudo->solved[y][x] = sudo->solved[y][with];
			sudo->solved[y][with] = tmp;
		}
		// printf("-----------------------\n");
	}
	y = rand() % 8;
	with = y + 3;
	with = with > 8 ? (with - 9) : with;
	// printf("y : %d | with : %d\n", y, with);
	y = start_subgrid(y);
	with = start_subgrid(with);
	// printf("y : %d | with : %d\n", y, with);
	y_end = y + 3;
	while (y < y_end)
	{
		x = -1;
		while (++x < 9)
		{
			tmp = sudo->solved[y][x];
			sudo->solved[y][x] = sudo->solved[with][x];
			sudo->solved[with][x] = tmp;
		}
		y++;
		with++;
	}
	x = rand() % 8;
	with = x + 3;
	with = with > 8 ? (with - 9) : with;
	// printf("x : %d | with : %d\n", x, with);
	x = start_subgrid(x);
	with = start_subgrid(with);
	// printf("x : %d | with : %d\n", x, with);
	x_end = x + 3;
	while (x < x_end)
	{
		y = -1;
		while (++y < 9)
		{
			tmp = sudo->solved[y][x];
			sudo->solved[y][x] = sudo->solved[y][with];
			sudo->solved[y][with] = tmp;
		}
		x++;
		with++;
	}
}

void	fill_grid(t_sudo *sudo)
{
	int		x;
	int		y;

	y = -1;
	while (++y < 9)
	{
		x = -1;
		while (++x < 9)
			sudo->grid[y][x] = sudo->solved[y][x];
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
