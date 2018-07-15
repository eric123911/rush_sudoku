/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eschnell <eschnell@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/14 12:33:42 by eschnell     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 19:29:33 by eschnell    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main.h"

void	exception(void)
{
	WRITE("Error\n", 6);
}

int		str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		validate_params(char **argv)
{
	int x;
	int	y;
	int	z;

	x = 1;
	z = 0;
	while (argv[x])
	{
		y = 0;
		if (str_len(argv[x]) != 9)
			return (1);
		while (argv[x][y])
		{
			if (argv[x][y] >= '1' && argv[x][y] <= '9')
				z++;
			y++;
		}
		x++;
	}
	if (z < 17)
		return (1);
	else
		return (0);
}

int		main(int argc, char **argv)
{
	if (argc != 10)
	{
		exception();
		return (-1);
	}
	else
	{
		if (validate_params(argv) == 1)
		{
			exception();
			return (-1);
		}
		else
		{
			read_board(argv);
			backtrack(0);
		}
	}
	return (0);
}
