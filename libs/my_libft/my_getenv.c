
#include "libft.h"

char	*my_getenv_by_list(const char *name)
{
	extern char	**environ;
	size_t		name_len;
	char		**env;

	name_len = ft_strlen(name);
	env = environ;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
			return (*env + name_len + 1);
		env++;
	}
	return (NULL);
}

static void	test(void)
{
	printf("My funct = PATH : %s\n", my_getenv_by_list("PATH"));
	printf("Or funct = PATH : %s\n", getenv("PATH"));
	printf("--------------------------\n");
	printf("My funct = HOME : %s\n", my_getenv_by_list("HOME"));
	printf("Or funct = HOME : %s\n", getenv("HOME"));
	printf("--------------------------\n");
	printf("My funct = ROOT : %s\n", my_getenv_by_list("ROOT"));
	printf("Or funct = ROOT : %s\n", getenv("ROOT"));
}
