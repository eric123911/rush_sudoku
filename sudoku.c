/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sudoku.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmanevy <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 10:44:35 by jmanevy      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 15:32:24 by eschnell    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "sudoku.h"

int	board[81];
int	op_count = 0;

void		read_board(int **tab)
{
	//char	c;
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 0;
	while (tab[k])
	{
		j = 0;
		while (tab[k][j])
		{
			printf("%c", board[k][j]);
			j++;
		}
	}
	/*
	while (k < 81)
	{
		j = 0;
		while (j < 9)
		{
			c = board[i][j];
			if (c >= '1' && c <= '9')
				board[k++] = c - '0';
			else if (c == '.')
				board[k++] = NONE;
			j++;
		}
		i++;
	}
	*/
}

void		show_board(void)
{
	int	c;
	int	l;
	int	x;

	l = -1;
	while (l++ < 9)
	{
		c = -1;
		while (c++ < 9)
		{
			x = l * 9 + c;
			write(1, &board[x] + '0', 1);
		}
		WRITE("\n", 1);
	}
	WRITE("\n", 1);
}

int		check_contraint_aux(int i)
{
	int	line;
	int	col;
	int	h;

	line = i / 9;
	col = i % 9;
	h = 0;
	while (h < 9)
	{
		if (h != line && board[h * 9 + col] == board[i])
			return (0);
		h++;
	}
	h = 0;
	while (h < 9)
	{
		if (h != col && board[line * 3 + h] == board[i])
			return (0);
		h++;
	}
	return (1);
}

int		check_contraint(int	i, int lb, int cb)
{
	int 	j;
	int		k;
	int		lr;
	int		cr;

	lr = (i / 9) % 3;
	cr = (i % 9) % 3;
	if (check_contraint_aux(i) == 0)
		return (0);
	j = 0;
	while (j < 3)
	{
		k = 0;
		while (k < 3)
		{
			if ((j != lr || k != cr) &&
					board[(lb * 3 + j) * 9 + (cb * 3 + k)] == board[i])
				return (0);
			k++;
		}
		j++;
	}
	return (1);
}

void	backtrack(int i)
{
	if (i == 81)
	{
		show_board();
		return ;
	}
	if (board[i] == NONE)
	{
		backtrack(i++);
		return ;
	}
	op_count++;
	board[i] = 1;
	while (board[i] <= 9)
	{
		if (check_contraint(i, i / 27, (i % 9) / 3))
			backtrack(i++);
		board[i]++;
	}
	board[i] = NONE;
}
