
#include "../../includes/minishell.h"

static int	check_following_pipes_in_loop(char *str, int i, int ret);
static int	check_error_pipes(int first_pipes, int sec_pipes);

/**
 * check_pipe_init_and_end - Validates the initial and final characters
 *                            of a command string.
 *
 * This function checks if the input string starts or ends with a pipe
 * character. If it does, an appropriate error message is generated.
 *
 * @param str: The input string containing the command line to be checked.
 *
 * @return int: Returns NO_ERROR if no errors are found, or ERROR if the
 *              string starts or ends with a pipe character.
 */

int	check_pipe_init_and_end(char *str)
{
	int	i;

	i = 0;
	if (str[i] == PIPE)
	{
		pipe_syntax_error(1);
		return (ERROR);
	}
	while (str[i])
		i++;
	if (str[i - 1] == PIPE)
	{
		pipe_syntax_error(1);
		return (ERROR);
	}
	return (NO_ERROR);
}

/**
 * check_following_pipes - Checks for consecutive pipes and validates their
 *                         syntax in a command string.
 *
 * This function iterates through the input string to ensure that no two
 * pipe characters are adjacent without a space in between. It calls a
 * helper function to validate the syntax whenever a pipe is detected.
 *
 * @param str: The input string containing the command line to be checked.
 *
 * @return int: Returns NO_ERROR if no syntax errors are found, or ERROR
 *              if there are consecutive pipes without proper spacing.
 */

int	check_following_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_following_pipes_in_loop(str, i, NO_ERROR) == ERROR)
			return (ERROR);
		i++;
	}
	return (NO_ERROR);
}

/**
 * check_following_pipes_in_loop - Helper function to analyze the input
 *                                  string for consecutive pipes.
 *
 * This function maintains static variables to track the state of pipe
 * characters and spaces encountered. It determines the appropriate
 * counts and checks for errors based on the pipe and space arrangement.
 *
 * @param str: The input string containing the command line to be checked.
 * @param i: The current index in the input string being analyzed.
 * @param ret: The current return status, which may be updated based on
 *             the analysis.
 *
 * @return int: Returns the updated status indicating whether an error
 *              was encountered during the validation.
 */

static int	check_following_pipes_in_loop(char *str, int i, int ret)
{
	static int	f_pipe = OFF;
	static int	space_between_pipes = 0;
	static int	count_first_pipes = 0;
	static int	count_sec_pipes = 0;

	if (str[i] == PIPE && f_pipe == OFF)
	{
		count_first_pipes += 1;
		f_pipe = ON;
	}
	else if (str[i] == SPACE_CHAR && f_pipe == ON)
		space_between_pipes = 1;
	else if (str[i] == PIPE && f_pipe == ON && space_between_pipes == 0)
		count_first_pipes += 1;
	else if (str[i] == PIPE && f_pipe == ON && space_between_pipes != 0)
		count_sec_pipes += 1;
	else if (str[i] != PIPE && str[i] != SPACE_CHAR && f_pipe == ON)
	{
		ret = check_error_pipes(count_first_pipes, count_sec_pipes);
		f_pipe = OFF;
		count_first_pipes = 0;
		count_sec_pipes = 0;
		space_between_pipes = 0;
	}
	return (ret);
}

/**
 * check_error_pipes - Validates the number of pipes and identifies syntax
 *                     errors.
 *
 * This function checks the counts of consecutive pipes detected in the
 * command string and determines if any syntax errors have occurred,
 * returning appropriate error statuses.
 *
 * @param first_pipes: The count of pipes detected before encountering a
 *                     non-pipe character.
 * @param sec_pipes: The count of pipes detected after encountering a
 *                   space character.
 *
 * @return int: Returns ERROR if a syntax error is found, or NO_ERROR
 *              if the pipe syntax is valid.
 */

static int	check_error_pipes(int first_pipes, int sec_pipes)
{
	if ((first_pipes == 1 || first_pipes == 2) && sec_pipes == 1)
		return (pipe_syntax_error(1));
	else if (first_pipes == 1 && sec_pipes >= 2)
		return (pipe_syntax_error(2));
	else if (first_pipes == 3)
		return (pipe_syntax_error(1));
	return (NO_ERROR);
}
