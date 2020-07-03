/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:25:27 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 16:29:14 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_env_var(char *var, char **env)
{
	t_list	*env_list;
	t_list	*new;

	if (!(env_list = ft_argv_to_list(env)))
		return (1);
	if (!(new = ft_lstnew((void*)var)))
		return (1);
	ft_lstadd_back(env_list, new);
	//free_argv(env, INT_MAX);
	if (!(env = list_to_argv(env_list)))
		return (1);
	return (1);
}

static int	export_check_syntax(char **argv)
{
	int		i;

	i = 0;
	if (!argv[1][0] || (!ft_isalpha(argv[1][0] && argv[1][0] != '_')))
		return (1);
	i++;
	while (argv[1][i] && argv[1][i] != '=')
	{
		if (!ft_isalnum(argv[1][i]) && argv[1][0] != '_')
			return (1);
		i++;
	}
	if (!argv[1][i])
		return (2);
	else
		return (0);
}

int		modify_env_var(int index, char **argv, char **env)
{
	
}

static int	export_envvar(int i, char **argv, char **env)
{
	char	*var;
	int		syntax_check;

	if ((syntax_check = export_check_syntax(argv)) == 1)
		return (1);
	else if (syntax_check == 2)
		return (0);
	else if (!(var = get_env(argv[i], env)))
		return (new_env_var(argv[i], env));
	else
	{
		free(var);
		modify_env_var(argv, env);
	}
}

int			builtin_export(char **argv, char **env)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!argv[1])
		return (builtin_env(env));
	while (argv[i])
	{
		if (export_envvar(i, argv, env))
			status = 1;
	}
	return (status);
}
