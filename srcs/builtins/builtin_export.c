/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:25:27 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/05 11:37:19 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_env_var(char *var)
{
	t_list	*env_list;
	t_list	*new;

	if (!(env_list = ft_argv_to_list(g_env)))
		return (1);
	if (!(new = ft_lstnew((void*)var)))
		return (1);
	ft_lstadd_back(&env_list, new);
	//free_argv(env, INT_MAX);
	if (!(g_env = list_to_argv(env_list)))
		return (1);
	return (1);
}

static int	export_check_syntax(char *arg)
{
	int		i;

	i = 0;
	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
	{
		return (1);
	}
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[0] != '_')
			return (1);
		i++;
	}
	if (!arg[i])
		return (2);
	else
		return (0);
}

static int	modify_env_var(int index, char **argv, char *var)
{
	t_list	*env_list;
	t_list	*nav;
	char	*to_cmp;
	char	*new_var;

	if (!(env_list = ft_argv_to_list(g_env)))
		return (1);
	if (!(new_var = ft_strdup(argv[index])))
		return (1);
	nav = env_list;
	while (nav)
	{
		to_cmp = (char*)nav->content;
		if (!ft_strncmp(to_cmp , (const char*)var, ft_strlen(var)) && to_cmp[ft_strlen(var)] == '=')
		{
			free(nav->content);
			if (!(nav->content = ft_strdup(argv[index])))
				return (1);
		}
		nav = nav->next;
	}
	if (!(g_env = list_to_argv(env_list)))
		return (1);
	return (0);
}

static int	export_envvar(int i, char **argv)
{
	char	*var;
	int		syntax_check;

	if ((syntax_check = export_check_syntax(argv[i])) == 1)
		return (1);
	else if (syntax_check == 2)
		return (0);
	if (!(var = ft_strndup(argv[i], ft_strlen_char(argv[i], '='))))
		return (1);
	if (!(get_env(var)))
		return (new_env_var(argv[i]));
	else
	{
		modify_env_var(i, argv, var);
		free(var);
	}
	return (1);
}


// PRINT_EXPORT:
// 	-sort sort
// 	-put value in ""
// 	-join "declar -x " with each line

// static int	print_export()
// {
	
// }

int			builtin_export(char **argv)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!argv[1])
		return (builtin_env(g_env));
	while (argv[i])
	{
		if (export_envvar(i, argv))
			status = 1;
		i++;
	}
	return (status);
}
