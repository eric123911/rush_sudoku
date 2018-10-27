/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sudoku.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eschnell <eschnell@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 18:18:42 by eschnell     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/21 10:07:20 by eschnell    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sudoku.h"

int	g_board[81];

void	read_board(char **lines)
{
	char	c;
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			c = lines[i][j];
			if (c >= '1' && c <= '9')
				g_board[k++] = c - '0';
			else if (c == '.')
				g_board[k++] = NONE;
			j++;
		}
		i++;
	}
}

void	show_board(void)
{
	int c;
	int l;
	int k;
	int nb;

	l = -1;
	WRITE("+-------+-------+-------+\n", 26);
	while (l++ < 8)
	{
		if (l == 3 || l == 6)
			WRITE("|-------+-------+-------|\n", 26);
		c = -1;
		while (c++ < 8)
		{
			k = l * 9 + c;
			if (c == 0 || c == 3 || c == 6)
				WRITE("| ", 2);
			nb = g_board[k] + '0';
			WRITE(&nb, 1);
			if (c != 8)
				WRITE(" ", 1);
		}
		WRITE(" |\n", 3);
	}
	WRITE("+-------+-------+-------+\n", 26);
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
		if (h != line && g_board[h * 9 + col] == g_board[i])
			return (0);
		h++;
	}
	h = 0;
	while (h < 9)
	{
		if (h != col && g_board[line * 9 + h] == g_board[i])
			return (0);
		h++;
	}
	return (1);
}

int		check_constraint(int i, int lb, int cb)
{
	int lr;
	int cr;
	int j;
	int k;

	if (check_contraint_aux(i) == 0)
		return (0);
	lr = (i / 9) % 3;
	cr = (i % 9) % 3;
	j = 0;
	while (j < 3)
	{
		k = 0;
		while (k < 3)
		{
			if ((j != lr || k != cr) &&
					g_board[(lb * 3 + j) * 9 + (cb * 3 + k)] == g_board[i])
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
	if (g_board[i] != NONE)
	{
		backtrack(i + 1);
		return ;
	}
	g_board[i] = 1;
	while (g_board[i] <= 9)
	{
		if (check_constraint(i, i / 27, (i % 9) / 3))
			backtrack(i + 1);
		g_board[i]++;
	}
	g_board[i] = NONE;
}
