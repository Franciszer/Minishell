/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:25:27 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/05 15:26:57 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_env_var(char *var)
{
	t_list	*env_list;
	t_list	*new;
	char	*var_copy;

	if (!(env_list = ft_argv_to_list(g_env)))
		return (1);
	if (!(var_copy = ft_strdup(var)))
		return (1);
	if (!(new = ft_lstnew((void*)var_copy)))
		return (1);
	ft_lstadd_back(&env_list, new);
	if (g_env_modified)
		free_argv(g_env, INT_MAX);
	if (!(g_env = list_to_argv(env_list)))
		return (1);
	g_env_modified = 1;
	ft_lstclear(&env_list, free);
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

	if (!(env_list = ft_argv_to_list(g_env)))
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
	if (g_env_modified)
		free_argv(g_env, INT_MAX);
	else
		g_env_modified = 1;	
	if (!(g_env = list_to_argv(env_list)))
		return (1);
	ft_lstclear(&env_list, free);
	return (0);
}

static int	export_envvar(int i, char **argv)
{
	char	*var;
	int		syntax_check;
	int		return_value;
	char	*to_free;

	if ((syntax_check = export_check_syntax(argv[i])) == 1)
		return (1);
	else if (syntax_check == 2)
		return (0);
	if (!(var = ft_strndup(argv[i], ft_strlen_char(argv[i], '='))))
		return (1);
	if (!(to_free = get_env(var)))
		return_value = new_env_var(argv[i]);
	else
	{
		free(to_free);
		return_value = modify_env_var(i, argv, var);
	}
	free(var);
	return (return_value);
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
