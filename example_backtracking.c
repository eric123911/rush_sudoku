#include <stdlib.h>
#include <stdio.h>

# define NONE 0

int	board[81];
int	k_count;

/* Lis la grille. La grille est codée avec uniquement les caractères (0 -> 9)
** et . pour un caractère inconnu. Les autres caracteres sont ignores. */
void	read_board(char **line)
{
	char	c;
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 0;
	while (k < 81)
	{
		j = 0;
		while (j < 9)
		{
			c = line[i][j];
			if (c >= '1' && c <= '9')
				board[k++] = c - '0';
			else if (c == '.')
			  	board[k++] = NONE;
			/*
			else if (!((c >= '1' && c <= '9') || c == '.'))
			{
				printf("J'ai segfault è.é\n");
				return (0);
			}
			*/
			j++;
		}
		i++;
	}
}

/* afficher la grille courante */
void	show_board(void)
{
	int	c;
	int	l;
	int	k;
	
	l = 0;
	while (l < 9)
	{
		c = 0;
		while (c < 9)
		{
			k = l * 9 + c;
			if (board[k] == NONE)
				printf(". ");
			else
				printf("%c ", board[k] + '0');
			c++;
		}
		printf("\n");
		l++;
	}
	printf("\n");
}

/* verifier toutes les contraintes qui font intervenir la case i */
int	check_constraint(int i)
{
	int l = i / 9;
	int c = i % 9;
	int lb = l / 3;
	int lr = l % 3;
	int cb = c / 3;
	int cr = c % 3;
	
	int l2;
	int c2;
	int lr2;
	int cr2;

	/* verifier la ligne contenant la case i */
	l2 = 0;
	while (l2 < 9)
	{
		if (l2 != l && board[l2 * 9 + c] == board[i])
			return 0;
		l2++;
	}

	/* verifier la colone contenant la case i */
	c2 = 0;
	while (c2 < 9)
	{
		if (c2 != c && board[l * 9 + c2] == board[i])
			return 0;
		c2++;
	}

	/* verifier la region (carre 3x3) contenant la case i */
	lr2 = 0;
	while (lr2 < 3)
	{
		cr2 = 0;
		while (cr2 < 3)
		{
			if ((lr2 != lr || cr2 != cr) &&
					board[(lb * 3 + lr2) * 9 + (cb * 3 + cr2)] == board[i])
				return 0;
			cr2++;
		}
		lr2++;
	}
	return 1;
}


/* resolution par backtracking, en supposant que toutes les cases
**  d'indices j<i ont deja ete remplies */
void	backtrack(int i)
{
	if (i == 81)
	{
		show_board();			/* afficher la solution */
		return;
	}
	if (board[i] != NONE)
	{
		backtrack(i++);			/* case deja remplie */
		return;
	}
	k_count++;
	board[i] = 1;
	while (board[i] <= 9)
	{
		if (check_constraint(i))
			backtrack(i++);
		board[i]++;
	}
	board[i] = NONE;	/* laisser la grille dans l'etat
                                ** ou on l'a trouvee en entrant */
}

int	main(int argc, char **argv)
{
	if (argc != 10)
	{
		printf("Erreur\n");
		return (0);
	}
	read_board(argv);
	show_board();
	backtrack(0);
	printf("%d noeuds cherchés\n", k_count);
	return 0;
}
