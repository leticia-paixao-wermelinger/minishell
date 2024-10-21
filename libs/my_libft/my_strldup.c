
#include "libft.h" 

char	*my_strldup(const char *s, int i)
{
	char	*dest;

	dest = (char *)malloc(i + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	my_strlcpy(dest, s, i + 1);
	return (dest);
}

/*
#include <stdio.h>

int	main()
{
	#include <string.h>

	const char	str[] = "Abacaxi";
	char	*dest2;

	dest2 = my_strcdup(str, 'c');
	printf("Minha pŕopria função strcdup(): %s\n", dest2);
	free(dest2);
	return (0);
}*/
