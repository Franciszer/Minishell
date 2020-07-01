/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:40:30 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/01 18:44:08 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../srcs/libft/libft.h"
# include "errors.h"
# include "colors.h"

# include <sys/types.h>
# include <sys/wait.h>

/*
**	DEFINES
*/

# define PROMPT_START_MSG "minishell$ "
# define MINISHELL_PATH "./minishell"
# define NB_COMMANDS 1

# define COMMAND0_NAME "hello_world"
# define COMMAND0_PATH "./srcs/commands/hello_world"

/*
**	STRUCTURES
*/

typedef	struct	s_commands
{
	char	**command_names;
	char	**command_paths;
}				t_commands;

/*
** ________FUNCTIONS________
*/

/*
**       ______PARSING_AND_TOKENIZATION_____
*/

t_list	*prompt_loop();
void	manage_quotes(char *quotes, char c);
int		isQuote(char c);
int		isSpecialChar(char *s);
char	*copy_token(char *str, size_t maxsize);
t_list	*tokenize(char *line);
size_t	get_token(char *tokenStart, t_list **tokenlist);
int		add_to_token_list(char *token, t_list **tokenlist);
size_t	tokenLen(char *tokenStart);
size_t	tokenLenSQuote(char *tokenStart);
size_t	tokenLenDQuote(char *tokenStart);
size_t	token_len_special(char *token_start);
int		free_argv(char **argv, int max_index);
char	**list_to_argv(t_list *token_list);
int		tokens_syntax_check(t_list *token_list);

/*
**       ______TOKEN_EXPANSION_____
*/

char	*get_env(char *key, char **env);
int		ft_strlen_key(char *key_start);
char	*expand_env(char *token, int *i, int *j, char **env);
void	*get_final_token(void *content, void *env);
t_list	*expand_tokens(t_list **token_list, char **env);
char	*expand_token_noquote(char *token, char **env);

/*
**		_____COMMANDS_____
*/

int		minishell_exit(t_list *token_list);
t_commands	*init_commands();
char	**init_command_names();
char	**init_command_paths();
int		get_command_index(char *command, t_commands *commands);
int		free_commands(t_commands *commands);
int		minishell_launch(char **argv);


/*
**		______UTILS______
*/

void	print_tokens(t_list *tokenlist);
void	print_argv(char **argv);
char	*remove_quotes_free(char *str, char quote);


#endif