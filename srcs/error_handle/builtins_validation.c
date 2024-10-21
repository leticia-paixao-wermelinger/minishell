
#include "../../includes/minishell.h"

/*
* For cd...
*/

int	validate_args(t_tokens *node)
{
	if (node && node->next != NULL)
	{
		print_cd_error("", ": too many arguments\n");
		return (ERROR);
	}
	return (NO_ERROR);
}
