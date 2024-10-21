
#include "../../includes/minishell.h"

/**
 * g_status - Manages the global status of the shell.
 *
 * This function retrieves or sets the global status value used by the shell.
 * If a non-negative integer is passed as an argument, it updates the global
 * status value. If a negative integer is passed, the function ignores it and
 * simply returns the current global status value.
 *
 * @param number: The new status value to set (must be non-negative). If a
 *                negative value is passed, the function returns the current
 *                status without modifying it.
 *
 * @return int: The current global status value after possible update.
 */

int	g_status(int number)
{
	static int	g_status = 0;

	if (number >= 0)
		g_status = number;
	return (g_status);
}
