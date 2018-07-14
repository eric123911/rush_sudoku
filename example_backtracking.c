#include <stdlib.h>
#include <stdio.h>

#define INCONNU 0

int grille[81];
int compteur_noeuds;

/* Lire la grille sur stdin. La grille est codée avec uniquement les
 *  caractères 0->9 et . pour une case inconnue. Les autres caracteres
 *   sont ignores. */
void lire_grille(char **ligne)
{
	char c;
	int	i;
	int	j;
	int k;

	i = 1, k = 0;
	while (k < 81)
	{
		j = 0;
		while (j < 9)
		{
			c = ligne[i][j];
			if (c >= '1' && c <= '9')
				grille[k++] = c - '0';
			else if (c == '.')
				grille[k++] = INCONNU;
			else if (!((c >= '1' && c <= '9') || c == '.'))
			{
				fprintf(stderr, "I segfaulted è.é\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

/* afficher la grille
** courante sur stdout */
void afficher_grille()
{
	int c;
	int l;
	int	k;
	
	l = 0;
	while (l < 9)
	{
		c = 0;
		while (c < 9)
		{
			k = l * 9 + c;
			if (grille[k] == INCONNU)
				printf(". ");
			else
				printf("%c ", grille[k] + '0');
			c++;
		}
		printf("\n");
		l++;
	}
	printf("\n");
}

/* verifier toutes les contraintes qui font intervenir la case i */
int verifier_constraintes(int i)
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

	/* verifier la colonne contenant la case i */
	l2 = 0;
	while (l2 < 9)
	{
		if (l2 != l && grille[l2 * 9 + c] == grille[i])
			return 0;
		l2++;
	}

	/* verifier la ligne contenant la case i */
	c2 = 0;
	while (c2 < 9)
	{
		if (c2 != c && grille[l * 9 + c2] == grille[i])
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
					grille[(lb * 3 + lr2) * 9 + (cb * 3 + cr2)] == grille[i])
				return 0;
			cr2++;
		}
		lr2++;
	}
	return 1;
}


/* resolution par backtracking, en supposant que toutes les cases
 *  d'indices j<i ont deja ete remplies */
void backtrack(int i)
{
	if (i == 81)
	{
		afficher_grille();			/* afficher la solution */
		return;
	}
	if (grille[i] != INCONNU)
	{
		backtrack(i + 1);			/* case deja remplie */
		return;
	}
	compteur_noeuds++;
	grille[i] = 1;
	while (grille[i] <= 9)
	{
		if (verifier_constraintes(i))
			backtrack(i + 1);
		grille[i]++;
	}
	grille[i] = INCONNU;			/* laisser la grille dans l'etat
                                    ** ou on l'a trouvee en entrant */
}

int main(int argc, char **argv)
{
	if (argc != 10)
	{
		printf("Erreur\n");
		return (0);
	}
	lire_grille(argv);
	afficher_grille();
	backtrack(0);
	printf("%d noeuds cherches\n", compteur_noeuds);
	return 0;
}
