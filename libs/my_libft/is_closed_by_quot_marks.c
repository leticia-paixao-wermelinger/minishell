
#include "libft.h"

int	is_closed_by_quot_marks(char *str)
{
	int	i;

	i = my_strlen(str) - 1;
	if (str[0] == 34 && str[i] == 34)
		return (1);
	else if (str[0] == 39 && str[i] == 39)
		return (1);
	return (0);
}
