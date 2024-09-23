/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:19:26 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/23 00:19:58 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum e_flag
{
	FALSE = 0,
	TRUE = 1,
	OFF = 2,
	ON = 3
};

/*
Valores Padrão:
0: Sucesso. O comando foi executado com sucesso.
1: Erro Geral. Indica uma falha genérica ou um erro não específico.
Erros Comuns:
127: Comando Não Encontrado. Código retornado quando o shell não consegue encontrar o comando especificado. É uma maneira padrão de indicar que o comando não foi encontrado no caminho especificado.
Outros Valores:
2-125: Podem ser utilizados por comandos e programas para indicar erros específicos. Esses valores são definidos pelos próprios programas e podem variar.
126: Comando Não Executável. Esse código indica que o comando foi encontrado, mas não é executável (por exemplo, se não tiver permissões de execução).
128: Usado para indicar que o comando foi terminado por um sinal. O código de saída é o número do sinal adicionado a 128 (por exemplo, 128 + 2 para SIGINT).

0: Success—Indicates that the command or program executed successfully without any errors.
1: General Error—A catch-all exit code for a variety of general errors. Often used when the command or program encounters an error, but no specific exit code is available for the situation.
2: Misuse of shell built-ins—Indicates incorrect usage of shell built-in commands or misuse of shell syntax.
126: Command cannot execute—The command was found, but it could not be executed, possibly due to insufficient permissions or other issues.
127: Command not found—The command was not found in the system's PATH, indicating that either the command does not exist or the PATH variable is incorrectly set.
128: Invalid exit argument—Returned when a script exits with an invalid argument. This usually indicates an error in the script itself.
128 + N: Fatal error signal N—Indicates that the command or program was terminated by a fatal error signal. For example, an exit code of 137 (128 + 9) means that the command was terminated by a SIGKILL signal.
130: Script terminated by Control-C—Indicates that the command or script was terminated by the user using Control-C (SIGINT signal).
255: Exit status out of range—Returned when the exit status is outside the valid range (0 to 254).
*/

enum e_error {
	NO_ERROR = 0,
	ERROR = 1,
	MISUSE = 2,
	CANT_EXEC = 126,
	NOT_FOUND = 127,
	INVALID_EXIT_ARG = 128,
	FATAL_ERROR_MINUS_N = 128,
	USED_CTRL_C = 130, // DONE
	EXIT_STATUS_OUT_RANGE = 255,
	CLOSE
};

enum e_ascii {
	DOUBLE_QUOT_MARK = 34,	// "
	SIMPLE_QUOT_MARK = 39,	// '
	PIPE = 124,				// |
	AMPERSAND = 38,			// &
	SEMICOLON = 59,			// ;
	OPEN_PARENTHESIS = 40,	// (
	CLOSE_PARENTHESIS = 41,	// )
	LESS_THAN = 60,			// <
	GREATER_THAN = 62,		// >
	DOLLAR = 36,			// $
	QUESTION_MARK = 63,		// ?
	FINAL_DOT = 46,			// .
	SPACE_CHAR = 32,		// space
	TAB_CHAR = 9,			// \t
	NEWLINE_CHAR = 10,		// \n
	UNPRINT_CHAR = 8,
	UNPRINT_PIPE = 8,		// backspace (|)
	UNPRINT_GT = 12,		// form feed (<)
	UNPRINT_LT = 13			// carriage ret (>)
};

enum e_token {
	NO_INFO = 0,
	COMMAND = 1,
	ARGUMENT = 2,
	BUILTIN = 4,
	EXEC = 5,
	T_PIPE = 124, // |
	REDIR_APPEND = 3, // >>
	REDIR_OUT = 62, // >
	REDIR_IN = 60, // <
	REDIR_HEREDOC = 6, // <<
	REDIR_FILE
};

#endif
