/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:12:42 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/11 11:04:47 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# define ERR_READLINE "an error has occured while reading input"

# define ERR_UNFINISHED_QUOTE "quote was not proprely closed"

# define ERR_UNEXPECTED_TOKEN "syntax error near unexpected token"

# define ERR_UNKNOWN_COMMAND "unknown command"

# define ERR_PID "error creating new process"

# define ERR_EXECVE "error executing command"

# define ERR_TOO_MANY_ARGS "too many arguments"

# define ERR_PIPE "Syntax error: near \'|\' ot \';\'"

# define ERR_SEMICOL "Syntax error: `;\' unexpected"

# define ERR_REDIR "syntax error near unexpected token `newline\'"
# define ERR_REDIR_2 "syntax error near unexpected token `>\'"
# define ERR_REDIR_1 "syntax error near unexpected token `>>\'"
# define ERR_REDIR_3 "syntax error near unexpected token `<\'"

# define ERR_REDIR_IS_DIR_P1 "cannot create "
# define ERR_REDIR_IS_DIR_P2 ": Is a directory"

# define ERR_REDIR_DONT_FIND_P1 "cannot open "
# define ERR_REDIR_DONT_FIND_P2 ": No such file or directory"

#endif
