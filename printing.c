/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:07:09 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/26 11:22:59 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sudoku.h"

void	print_color(char *color, int num, int nl)
{
	int		x;

	x = -1;
	while (++x < num)
		printf("%s", color);
	if (nl)
		printf("\n");
	printf("\e[0m");
}

void	print_VLine(int x)
{
	if (!((x + 1) % 3))
		print_color("\e[0;32m|", 1, 0);
	else
		print_color("|", 1, 0);
}

void	print_HLine(int x, int y)
{
	x = -1;
	printf("\n   ");
	while (++x < 37)
	{
		if (!((x) % 12) && x &&  x != 36 && y != 8)
			print_color("\e[0;32m+", 1, 0);
		else if (!((y + 1) % 3) || !x || x == 36)
			print_color("\e[0;32m-", 1, 0);
		else
			print_color("-", 1, 0);
	}
	printf("\n");
}

void	print_solved(t_sudo *sudo)
{
	int		x;
	int		y;

	print_color("\e[0;32m-", 37, 1);
	x = -1;
	y = -1;
	while (++y < 9)
	{
		print_color("\e[0;32m|", 1, 0);
		x = -1;
		while (++x < 9)
		{
			if (sudo->fixed[y][x])
				printf(" \e[0;34m%d\e[0m ", sudo->solved[y][x]);
			else
				printf(" \e[0;32m%d\e[0m ", sudo->solved[y][x]);
			print_VLine(x);
		}
		print_HLine(x, y);
	}
	printf("\n");
}

void	print_grid(t_sudo *sudo)
{
	int		x;
	int		y;

	printf("\n\e[0;34mInput:\e[0m -a y x n | \e[0;34mErase:\e[0m -e y x | \e[0;34mExit: \e[0mexit\n\n");
	while (sudo->grids--)
		write(1, "\033[1A\r\033[K", 8);
	printf("\e[0;32my\e[0;34m\\\e[0;32mx\e[0;33m  0   1   2   3   4   5   6   7   8\n   \e[0m");
	print_color("\e[0;32m-", 37, 1);
	y = -1;
	while (++y < 9)
	{
		printf("\e[0;33m%d  \e[0m", y);
		print_color("\e[0;32m|", 1, 0);
		x = -1;
		while (++x < 9)
		{
			if (sudo->fixed[y][x])
				printf(" \e[0;34m%d\e[0m ", sudo->grid[y][x]);
			else if (!sudo->grid[y][x])
				printf(" %d ", sudo->grid[y][x]);
			else if (sudo->grid[y][x] == sudo->solved[y][x])
				printf(" \e[0;32m%d\e[0m ", sudo->grid[y][x]);
			else
				printf(" \e[0;31m%d\e[0m ", sudo->grid[y][x]);
			print_VLine(x);
		}
		print_HLine(x, y);
	}
	printf("\n");
	sudo->grids = 25;
}

void	print_bits(t_sudo *sudo)
{
	int		x;

	x = -1;
	printf("--------rows-----------\n");
	while (++x < 9)
		printf("row[%d] : %d\n", x, sudo->row[x]);
	x=-1;
	printf("--------cols-----------\n");
	while (++x < 9)
		printf("col[%d] : %d\n", x, sudo->col[x]);
	x=-1;
	printf("--------cells----------\n");
	while (++x < 9)
		printf("cell[%d] : %d\n", x, sudo->cell[x]);
}

/*
-------------------------------------
| 3 | 0 | 6 | 5 | 0 | 8 | 4 | 0 | 0 |
------------+-----------+------------
| 5 | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
------------+-----------+------------
| 0 | 8 | 7 | 0 | 0 | 0 | 0 | 3 | 1 |
------------+-----------+------------
| 0 | 0 | 3 | 0 | 1 | 0 | 0 | 8 | 0 |
------------+-----------+------------
| 9 | 0 | 0 | 8 | 6 | 3 | 0 | 0 | 5 |
------------+-----------+------------
| 0 | 5 | 0 | 0 | 9 | 0 | 6 | 0 | 0 |
------------+-----------+------------
| 1 | 3 | 0 | 0 | 0 | 0 | 2 | 5 | 0 |
------------+-----------+------------
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 7 | 4 |
------------+-----------+------------
| 0 | 0 | 5 | 2 | 0 | 6 | 3 | 0 | 0 |
-------------------------------------
*/