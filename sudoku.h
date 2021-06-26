/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:07:32 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/26 11:20:04 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Libft/libft.h"

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define BLU "\e[0;34m"
#define YEL "\e[0;33m"
#define reset "\e[0m"

typedef struct	s_sudo
{
	int			solved[9][9];
	int			grid[9][9];
	int			fixed[9][9];
	char		*input;
	short int	row[9];
	short int	col[9];
	short int	cell[9];
	int			grids;
}				t_sudo;

void	print_HLine(int x, int y);
void	print_VLine(int x);
void	print_color(char *color, int num, int nl);
void	print_grid(t_sudo *sudo);
void	print_solved(t_sudo *sudo);
void	print_bits(t_sudo *sudo);
void	err_msg(t_sudo *sudo, char *msg);
int		if_solved(t_sudo *sudo);

int		which_cell(int x, int y);
int		check_if_break(t_sudo *sudo, int x, int y, int num);
void	fixed_fields(t_sudo *sudo);
void	solve_sudoku(t_sudo *sudo);
void	fill_grid(t_sudo *sudo, int grid[9][9]);
void	prev(int *x, int *y);

//011111111



//000100000
//111111111
//^
//111011111
//011111111
//&
//011011111
//ADD(1,1,1)