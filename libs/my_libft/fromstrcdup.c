
#include "libft.h" 

static size_t	strcopyfromc(char *dst, const char *src, int start)
{
	unsigned int	i;

	i = 0;
	while (src[start])
	{
		dst[i] = src[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (i);
}

char	*fromstrcdup(const char *s, char c)
{
	char	*dest;
	int		size;
	int		i;
	int		j;

	size = 0;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	j = i;
	while (s[j++])
		size++;
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	strcopyfromc(dest, s, (i + 1));
	return (dest);
}
/*
#include <stdio.h>

int	main()
{
	#include <string.h>

	const char	str[] = "Abacaxi";
	char	*dest2;

	dest2 = fromstrcdup(str, 'c');
	printf("fromstrcdup(): %s\n", dest2);
	free(dest2);
	return (0);
}*/
