
#include "../../includes/minishell.h"

void	print_cd_error(char *str, char *err)
{
	print_error("minishell: cd: ");
	print_error(str);
	print_error(err);
}
