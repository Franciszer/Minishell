/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:40:30 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 14:58:41 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../srcs/libft/libft.h"
# include "errors.h"
# include "colors.h"

# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

/*
**	DEFINES
*/

# define PROMPT_START_MSG "minishell$ "
# define MINISHELL_PATH "./minishell"

# define BUILTIN_CD 0
# define BUILTIN_EXIT 1
# define BUILTIN_PWD 2
# define BUILTIN_ENV 3
# define BUILTIN_ECHO 4	

# define SAVE_POINTERS_TO_EXIT 0
# define EXIT_NOW 1

/*
** ________FUNCTIONS________
*/

/*
**       ______PARSING_AND_TOKENIZATION_____
*/

t_list			*prompt_loop();
void			manage_quotes(char *quotes, char c);
int				isQuote(char c);
int				isSpecialChar(char *s);
char			*copy_token(char *str, size_t maxsize);
t_list			*tokenize(char *line);
size_t			get_token(char *tokenStart, t_list **tokenlist);
int				add_to_token_list(char *token, t_list **tokenlist);
size_t			tokenLen(char *tokenStart);
size_t			tokenLenSQuote(char *tokenStart);
size_t			tokenLenDQuote(char *tokenStart);
size_t			token_len_special(char *token_start);
int				tokens_syntax_check(t_list *token_list);

/*
**       ______TOKEN_EXPANSION_____
*/

char			*get_env(char *key, char **env);
int				ft_strlen_key(char *key_start);
char			*expand_env(char *token, int *i, int *j, char **env);
void			*get_final_token(void *content, void *env);
t_list			*expand_tokens(t_list **token_list, char **env);
char			*expand_token_noquote(char *token, char **env);
size_t			ft_strlen_etokens(char *s, char **env);
int				is_specialchar_dquote(char c);

/*
**		_____COMMANDS_____
*/

t_list			*get_command_list(t_list *token_list);
int				execute_commands(t_list **commandlist, char **env);
void			free_commandlist(t_list *commandlist);
void			exit_minishell(int exit_code, int action, t_list **commandlist, char ***args);
int				minishell_launch(char **argv, char **env);
char			*search_path(char *command, char **env);

/*
**		_____BUILTINS_____
*/

int				is_builtin(char *command);
int				launch_builtin(int builtin_id, char **argv, char **env);
int				builtin_cd(char **args, char **env);
int				builtin_exit(char **args);
int				builtin_pwd(char **env);
int				builtin_env(char **env);
int				builtin_echo(char **argv);


/*
**		______UTILS______
*/

void			print_tokens(t_list *tokenlist);
void			print_argv(char **argv);
char			*remove_quotes_free(char *str, char quote);

#endif
