/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:40:30 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/25 15:06:06 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../srcs/libft/libft.h"
# include "errors.h"
# include "colors.h"

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>

/*
**	DEFINES
*/

# define PROMPT_START_MSG "minishell$ "
# define PIPE_START_MSG "> "

# define MINISHELL_PATH "./minishell"

# define BUILTIN_CD 0
# define BUILTIN_EXIT 1
# define BUILTIN_PWD 2
# define BUILTIN_ENV 3
# define BUILTIN_ECHO 4
# define BUILTIN_EXPORT 5
# define BUILTIN_UNSET 6

# define SAVE_POINTERS_TO_EXIT 0
# define EXIT_NOW 1

/*
**	 ________GLOBAL_VARIABLES________
*/

char				**g_env;
int					g_env_modified;
int					g_exit_status;
int					g_p_stop_sig;
int					g_open_pipe;
int					g_pipe_error;
int					g_man;
int					g_semicol_error;
int					g_first_is_envvar;
int					g_in_fork;

/*
**		______STRUCTS______
*/

typedef struct		s_redir
{
	int				in;
	int				putfile;
	int				putendfile;
	char			*file;
}					t_redir;

typedef struct		s_quotes
{
	int				q;
	int				dq;
}					t_quotes;

typedef struct		s_int2
{
	int				a;
	int				b;
}					t_int2;

typedef struct		s_size_t2
{
	int				a;
	int				b;
}					t_size_t2;

typedef struct		s_expand_tk_dt
{
	t_int2			ij;
	int				pb;
	char			*tmp;
	char			*final_token;
	int				is_err;
	t_quotes		qt;
}					t_expand_tk_dt;

/*
** ________FUNCTIONS________
*/

void				minishell_start();

/*
**       ______PARSING_AND_TOKENIZATION_____
*/

void				print_prompt();
t_list				*prompt_loop(int depth);
void				manage_quotes(char *quotes, char c);
int					is_quote(char c);
int					is_special_char(char *s);
char				*copy_token(char *str, size_t maxsize);
t_list				*tokenize(char *line);
size_t				get_token(char *token_start, t_list **tokenlist);
int					add_to_token_list(char *token, t_list **tokenlist);
size_t				ftoken_len(char *tok_s);
size_t				token_len_special(char *token_start);
int					tokens_syntax_check(t_list *token_list);
int					pipes_syntax_check(t_list *token_list);
char				*last_token(t_list *tokenlist);
char				*first_token(t_list *token_list);

/*
**		_____MINISHELL_LAUNCH_____
*/

int					path_searching(char **argv, char **tmp);
int					redir_error(t_redir redir);
void				parent(pid_t *pid, int *save, int fd[2]);
void				child(t_int2 save_last, int contain_putfile,
							char ***argv, int fd[2]);
int					preprocess_minishell(char ***argv);
void				sigtest(int sig);
char				**copy_argv(char **argv);
int					contain_redir(char **argv);
t_list				*do_redir(char ***argv);

/*
**       ______TOKEN_EXPANSION_____
*/

char				*get_env(char *key);
int					ft_strlen_key(char *key_start);
char				*eev(char *token, char *final_token, int *i, int *j);
void				*get_final_token(void *content);
t_list				*expand_tokens(t_list *token_list);
char				*expand_token_quote(char *tk, t_expand_tk_dt d);
size_t				ft_strlen_etokens(char *s);
int					is_specialchar_dquote(char c);
int					is_quote_only(char *tk);
char				*return_token(char **tk, int check_quote);
int					expand_quote_set_vals(char *tk,\
					t_expand_tk_dt *d, int *check_quote);
char				*return_expand_tk_quote(t_expand_tk_dt *d, int check_quote);

/*
**		_____COMMANDS_____
*/

t_list				*get_command_list(t_list *token_list);
int					execute_commands(t_list **commandlist);
void				free_commandlist(t_list **commandlist);
void				exit_minishell(int action, t_list *token_list,
									t_list **commandlist, char ***args);
int					minishell_launch(char **argv, int *start, int islast);
char				*search_path(char *command);
int					execute_pipes(t_list **commandlist);
t_list				*pipe_handle(int depth, t_list **token_list);

/*
**		_____BUILTINS_____
*/

int					is_builtin_child(char *command);
int					is_builtin_parent(char **command);
int					is_builtin_parent_2(char *command);
int					launch_builtin_child(int builtin_id, char **argv);
int					launch_builtin_parent(int builtin_id, char **argv);
int					builtin_cd(char **args);
int					ft_go_home(char *current_dir);
int					builtin_exit(char **args);
int					builtin_pwd();
int					builtin_env();
int					builtin_echo(char **argv);
int					builtin_unset(char **argv);

/*
**		__EXPORT__
*/

int					new_env_var(char *var);
int					export_check_syntax(char *arg);
int					modify_env_var_loop(t_list **env_list, char *var,
										char **argv, int index);
int					modify_env_var(int index, char **argv, char *var);
char				*added_var(char *arg);
int					export_envvar(int i, char **argv);
int					all_env_written(char *env_written, size_t len);
void				print_export_loop(char **env_written, size_t len);
int					print_export(void);
int					builtin_export(char **argv);
char				*remove_plus_sign(char *arg);
t_list				*replance_envvar_init_vals(int *replaced);
int					replace_envvar_util(t_list *nav, char *arg);
int					replace_envvar(char *arg);

/*
**		_____SIGNAL_HANDLING_____
*/

void				sigint_handler(int signo);
void				sigquit_handler(int sig);
void				signal_default();

/*
**		______UTILS______
*/

void				print_tokens(t_list *tokenlist);
void				print_argv(char **argv);

/*
**		_____REDIRECTION_____
*/

t_redir				stock_redir(char **cmd);
int					redirection(t_redir redir, int (*pipefd)[2],
								int *save);
void				cmd_to_rafter(char ***cmd);
int					is_redir(char *cmd);
int					is_dir(t_redir redir);
int					file_not_found(t_redir redir);
void				check_file(char **file);
char				*quoted_redir(char *tk);

/*
**		_____EXPAND_TOKEN_____
*/

char				*init_expand(t_quotes *qt, t_int2 *ij, int *pb, char *tk);
int					if_loop(char *tk, t_int2 *ij, t_quotes *qt, int *pb);
char				*elif_loop(char **final_token, char **tmp);
void				else_loop(char *tk, char **final_token,\
					t_int2 *ij, t_quotes *qt);
int					elif_test(char *tk, t_quotes qt, t_int2 ij);
char				*return_token(char **tk, int check_quote);

#endif
