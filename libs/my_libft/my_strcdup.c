
#include "libft.h" 

char	*my_strcdup(const char *s, char c)
{
	char	*dest;
	int		size;

	size = 0;
	while (s[size] != c)
		size++;
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	my_strlcpy(dest, s, (size + 1));
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
