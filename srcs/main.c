/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:39:32 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/26 18:56:44 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_and_throw(char *err, t_list **to_clear)
{
	ft_lstclear(to_clear, free);
	ft_perror(err);
}

void	minishell_start(void)
{
	t_list	*token_list;
	t_list	*command_list;

	if ((token_list = prompt_loop(0)))
	{
		if (!tokens_syntax_check(token_list))
			clear_and_throw(ERR_UNFINISHED_QUOTE, &token_list);
		else
		{
			command_list = get_command_list(token_list);
			execute_pipes(&command_list);
			ft_lstclear(&token_list, free);
			free_commandlist(&command_list);
		}
	}
	else
		return ;
}

int		copy_env(char ***env)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	if (!(new_env = (char**)malloc(sizeof(char*) * (i + 1))))
		return (0);
	i = 0;
	while ((*env)[i])
	{
		if (!(new_env[i] = ft_strdup((*env)[i])))
			return (0);
		i++;
	}
	new_env[i] = NULL;
	g_env = new_env;
	g_env_modified = 1;
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	g_open_pipe = 0;
	g_pipe_error = 0;
	g_exit_status = 0;
	g_semicol_error = 0;
	g_man = 0;
	g_in_fork = 0;
	if (argc > 1 || argv[1])
	{
		ft_perror("ERR_TOO_MANY_ARGS");
		return (1);
	}
	if (!copy_env(&env))
		return (!ft_perror("allocation error") ? 1 : 1);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		if (!g_p_stop_sig)
			print_prompt();
		minishell_start();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, sigquit_handler);
	}
	return (0);
}
