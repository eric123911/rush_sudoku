/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eschnell <eschnell@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/14 12:33:42 by eschnell     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 15:19:26 by eschnell    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sudoku.h"

int		exception(void)
{
	WRITE("Error\n", 6);
	return (0);
}

/*
int		check_params(char **board)
{
	int	x;
	int	y;

	x = 1;
	while (board[x])
	{
		y = 0;
		while (board[x][y])
		{
			if (board[x][y] != 46 || (board[x][y] < 48 && board[x][y] > 58))
				exception();
			y++;
		}
		if (y != 8)
			exception();
		x++;
	}

} */

int		main(int argc, char **argv)
{
	if (argc != 10)
		exception();
	//check_params(argv);
	read_board(argv);
	show_board();
	backtrack(0);
	return (0);
}
