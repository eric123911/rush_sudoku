/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eschnell <eschnell@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 18:09:01 by eschnell     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 19:31:01 by eschnell    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "sudoku.h"

void	exception(void);
void	check_params(char **argv);
void	read_board(char **lines);
void	show_board(void);
int		backtrack(int i);

#endif
