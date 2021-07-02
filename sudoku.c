/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:08:01 by ybouddou          #+#    #+#             */
/*   Updated: 2021/07/02 16:05:40 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sudoku.h"

void	fixed_fields(t_sudo *sudo)
{
	int		x;
	int		y;
	int		cell;

	cell = 0;
	y = -1;
	while (++y < 9)
	{
		x = -1;
		while (++x < 9)
		{
			if (sudo->grid[y][x] != 0)
			{
				sudo->fixed[y][x] = 1;
				sudo->row[y] = (1 << (sudo->grid[y][x] - 1)) | sudo->row[y];
				sudo->col[x] = (1 << (sudo->grid[y][x] - 1)) | sudo->col[x];
				cell = which_cell(x, y);
				sudo->cell[cell] = (1 << (sudo->grid[y][x] - 1)) | sudo->cell[cell];
			}
		}
	}
}

void	if_reach_max(t_sudo *sudo, int *x, int *y)
{
	if (sudo->solved[(*y)][(*x)] >= 10)
	{
		sudo->solved[(*y)][(*x)] = 0;
		do
			prev(x, y);
		while (sudo->fixed[(*y)][(*x)]);
		if (!sudo->fixed[(*y)][(*x)])
		{	
			sudo->row[(*y)] = ((1 << (sudo->solved[(*y)][(*x)] - 1)) ^ 511) & sudo->row[(*y)];
			sudo->col[(*x)] = ((1 << (sudo->solved[(*y)][(*x)] - 1)) ^ 511) & sudo->col[(*x)];
			sudo->cell[which_cell(*x, *y)] = ((1 << (sudo->solved[(*y)][(*x)] - 1)) ^ 511) & sudo->cell[which_cell(*x, *y)];
		}
	}
	else if (*x < 8)
		(*x)++;
}

void	solve_sudoku(t_sudo *sudo)
{
	int			y;
	int			x;
	
	y = 0;
	x = 0;
	while (y < 9)
	{
		if (!sudo->fixed[y][x]) 
		{
			do
				sudo->solved[y][x]++;
			while (sudo->solved[y][x] < 10 && check_if_break(sudo, x, y, sudo->solved[y][x]));
			if_reach_max(sudo, &x, &y);
			if (sudo->row[y] == 511)
			{
				y++;
				x = 0;
			}
		}
		else if (x < 8)
			x++;
	}
}

void	user_input(t_sudo *sudo)
{
	while (1)
	{
		ft_putstr_fd("\e[0;32mcommand: \e[0m", 1);
		get_next_line(0, &sudo->input);
		if (!ft_strncmp("-a ", sudo->input, 2) && ft_strlen(sudo->input) == 8)
		{
			sudo->y = ft_atoi(sudo->input + 3);
			sudo->x = ft_atoi(sudo->input + 5);
			sudo->n = ft_atoi(sudo->input + 7);
			if (!sudo->fixed[sudo->y][sudo->x])
				sudo->grid[sudo->y][sudo->x] = sudo->n;
			else
				err_msg(sudo, "you can't change a fixed spot!!");
		}
		else if (!ft_strncmp("-e ", sudo->input, 2) && ft_strlen(sudo->input) == 6)
		{
			sudo->y = ft_atoi(sudo->input + 3);
			sudo->x = ft_atoi(sudo->input + 5);
			if (!sudo->fixed[sudo->y][sudo->x])
				sudo->grid[sudo->y][sudo->x] = 0;
			else
				err_msg(sudo, "you can't change a fixed spot!!");
		}
		else if (!ft_strcmp("exit", sudo->input))
			exit (0);
		else
			err_msg(sudo, "wrong input!!");
		print_grid(sudo);
		free(sudo->input);
		if (if_solved(sudo))
		{
			printf("\e[0;32m***********Congratulations!!!***********\e[0m\n\n");
			exit (0);
		}
	}
}

int		all_cells(t_sudo *sudo)
{
	int		x;
	int		res;

	res = 0;
	x = -1;
	while (++x < 9)
		res += set_bits(sudo->cell[x]);
	return (res);
}

int		check_fixed(t_sudo *sudo, int x, int y)
{
	int		cell;
	int		bits;

	cell = which_cell(x, y);
	bits = set_bits(sudo->cell[cell]);
	if (!sudo->grid[y][x] || bits < 4)
		return (1);
	sudo->cell[cell] = ((1 << (sudo->grid[y][x] - 1)) ^ 511) & sudo->cell[cell];
	sudo->grid[y][x] = 0;
	return (0);
}

void	set_fixed(t_sudo *sudo)
{
	int		x;
	int		y;

	while (all_cells(sudo) > 36)
	{
		do
		{
			x = rand() % 9;
			y = rand() % 9;
		} while (check_fixed(sudo, x, y));
	}
}

int main()
{
	t_sudo	sudo;
	// int		grid[9][9] = {0};
	// int		grid[9][9] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
	// 					{5, 2, 0, 0, 0, 0, 0, 0, 0},
	// 					{0, 8, 7, 0, 0, 0, 0, 3, 1},
	// 					{0, 0, 3, 0, 1, 0, 0, 8, 0},
	// 					{9, 0, 0, 8, 6, 3, 0, 0, 5},
	// 					{0, 5, 0, 0, 9, 0, 6, 0, 0},
	// 					{1, 3, 0, 0, 0, 0, 2, 5, 0},
	// 					{0, 0, 0, 0, 0, 0, 0, 7, 4},
	// 					{0, 0, 5, 2, 0, 6, 3, 0, 0}};

	sudo = (t_sudo){0};
	sudo.fixed[0][0] = (int){0};
	sudo.solved[0][0] = (int){0};
	sudo.row[0] = (short int){0};
	sudo.col[0] = (short int){0};
	sudo.cell[0] = (short int){0};
	sudo.shuffled[0] = (short int){0};
	sudo.cell_shuffle[0] = (short int){0};
	solve_sudoku(&sudo);
	shuffle(&sudo);
	fill_grid(&sudo);
	set_fixed(&sudo);
	fixed_fields(&sudo);
	print_grid(&sudo);
	// print_solved(&sudo);
	user_input(&sudo);
	return (0);
}