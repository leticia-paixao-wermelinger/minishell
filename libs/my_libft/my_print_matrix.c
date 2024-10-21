
#include "libft.h"

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		my_printf("Str[%i] da matriz: %s\n", i, matrix[i]);
		i++;
	}
}
