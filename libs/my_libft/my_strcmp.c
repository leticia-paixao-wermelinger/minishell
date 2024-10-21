
#include "libft.h"

int	my_strcmp(const char *s1, const char *s2)
{
	size_t	count;
	int		cmp;

	count = 0;
	cmp = 0;
	while ((s1[count] || s2[count]))
	{
		cmp = (unsigned char)s1[count] - (unsigned char)s2[count];
		if (s1[count] != s2[count])
			return (cmp);
		count++;
	}
	return (cmp);
}
/*
#include <string.h>
#include <stdio.h>

int	main()
{
	char	str1[] = "testee";
	char	str2[] = "teste";
	int	dif;

	dif = my_strcmp(str1, str2);
	printf("%i\n", dif);

	printf("Minha função: %i \n", ft_strcmp("test\200", "test\0"));
	printf("Função original: %i, \n", strcmp("test\200", "test\0"));
}*/
