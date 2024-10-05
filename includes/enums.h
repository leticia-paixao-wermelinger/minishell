/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:19:26 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/30 14:58:03 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

/**
 * enum e_flag - Represents boolean and toggle states.
 * 
 * This enumeration defines simple boolean states: FALSE (0), TRUE (1), 
 * and toggle states OFF (2) and ON (3).
 */

enum e_flag
{
	FALSE = 0,
	TRUE = 1,
	OFF = 2,
	ON = 3
};

/**
 * enum e_error - Defines error codes for command execution and shell behavior.
 * 
 * This enumeration includes standard exit statuses used in the shell:
 * - NO_ERROR: Command executed successfully.
 * - ERROR: General error occurred.
 * - MISUSE: Incorrect usage of shell built-ins.
 * - CANT_EXEC: Command found but not executable.
 * - NOT_FOUND: Command not found in the system's PATH.
 * - INVALID_EXIT_ARG: Script exited with an invalid argument.
 * - USED_CTRL_C: Command terminated by Ctrl-C (SIGINT).
 * - EXIT_STATUS_OUT_RANGE: Exit status is outside valid range (0-254).
 * 
 * Additional values (128 + N) indicate termination by fatal error signals.
 */

enum e_error {
	NO_ERROR = 0,
	ERROR = 1,
	MISUSE = 2,
	CANT_EXEC = 126,
	NOT_FOUND = 127,
	INVALID_EXIT_ARG = 128,
	FATAL_ERROR_MINUS_N = 128,
	USED_CTRL_C = 130,
	EXIT_STATUS_OUT_RANGE = 255,
	CLOSE
};

/**
 * enum e_ascii - Represents ASCII values of special characters.
 * 
 * This enumeration defines ASCII values for various characters used in 
 * shell commands, such as quotation marks, pipes, and redirection symbols.
 * 
 *  DOUBLE_QUOT_MARK = "
 * 	SIMPLE_QUOT_MARK = '
 * 	PIPE = |
 * 	AMPERSAND = &
 * 	SEMICOLON = ;
 * 	OPEN_PARENTHESIS = (
 * 	CLOSE_PARENTHESIS = )
 * 	LESS_THAN = <
 * 	GREATER_THAN = >
 * 	DOLLAR = $
 * 	QUESTION_MARK = ?
 * 	FINAL_DOT = .
 * 	SPACE_CHAR = space
 * 	TAB_CHAR = \t
 * 	NEWLINE_CHAR = \n
 * 	UNPRINT_CHAR = backspace (|)
 * 	UNPRINT_PIPE = backspace (|)
 * 	UNPRINT_GT = form feed (<)
 * 	UNPRINT_LT = carriage ret (>)
 */

enum e_ascii {
	DOUBLE_QUOT_MARK = 34,
	SIMPLE_QUOT_MARK = 39,
	PIPE = 124,
	AMPERSAND = 38,
	SEMICOLON = 59,
	OPEN_PARENTHESIS = 40,
	CLOSE_PARENTHESIS = 41,
	LESS_THAN = 60,
	GREATER_THAN = 62,
	DOLLAR = 36,
	QUESTION_MARK = 63,
	FINAL_DOT = 46,
	SPACE_CHAR = 32,
	TAB_CHAR = 9,
	NEWLINE_CHAR = 10,
	UNPRINT_CHAR = 7,
	UNPRINT_PIPE = 8,
	UNPRINT_GT = 12,
	UNPRINT_LT = 13
};

/**
 * enum e_token - Defines token types for command parsing.
 * 
 * This enumeration specifies different token types recognized by the 
 * shell, including commands, arguments, built-ins, and redirection types.
 * 
 * T_PIPE = 124, // |
 * REDIR_APPEND = 3, // >>
 * REDIR_OUT = 62, // >
 * REDIR_IN = 60, // <
 * REDIR_HEREDOC = 6, // <<
 */

enum e_token {
	NO_INFO = 0,
	COMMAND = 1,
	ARGUMENT = 2,
	BUILTIN = 4,
	EXEC = 5,
	T_PIPE = 124,
	REDIR_APPEND = 3,
	REDIR_OUT = 62,
	REDIR_IN = 60,
	REDIR_HEREDOC = 6,
	REDIR_FILE = 7,
	HEREDOC_EOF
};
#endif
