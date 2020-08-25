/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:36:48 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/25 12:46:44 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			new_env_var(char *var)
{
	t_list	*env_list;
	t_list	*new;
	char	*var_copy;

	if (!(env_list = ft_argv_to_list(g_env))
		|| !(var_copy = ft_strdup(var))
		|| !(new = ft_lstnew((void*)var_copy)))
		return (1);
	ft_lstadd_back(&env_list, new);
	if (g_env_modified)
		free_argv(g_env, INT_MAX);
	if (!(g_env = list_to_argv(env_list)))
		return (1);
	g_env_modified = 1;
	ft_lstclear(&env_list, free);
	return (0);
}

int			export_check_syntax(char *arg)
{
	int		i;

	i = 1;
	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (1);
	while (arg[i] && arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '='))
		if (!ft_isalnum(arg[i++]) && arg[0] != '_')
			return (1);
	if (arg[i] == '+' && arg[i + 1] == '=')
		return (3);
	if (!arg[i])
		return (2);
	else
		return (0);
}

int			modify_env_var_loop(t_list **env_list, char *var, char **argv,
								int index)
{
	char	*to_cmp;
	t_list	*nav;

	nav = *env_list;
	while (nav)
	{
		to_cmp = (char*)nav->content;
		if (!ft_strncmp(to_cmp, (const char*)var, ft_strlen(var))
			&& to_cmp[ft_strlen(var)] == '=')
		{
			free(nav->content);
			if (!(nav->content = ft_strdup(argv[index])))
				return (1);
		}
		nav = nav->next;
	}
	return (0);
}

int			modify_env_var(int index, char **argv, char *var)
{
	t_list	*env_list;

	if (!(env_list = ft_argv_to_list(g_env))
		|| modify_env_var_loop(&env_list, var, argv, index))
		return (1);
	if (g_env_modified)
		free_argv(g_env, INT_MAX);
	else
		g_env_modified = 1;
	if (!(g_env = list_to_argv(env_list)))
		return (1);
	ft_lstclear(&env_list, free);
	return (0);
}

char		*added_var(char *arg)
{
	size_t	i;
	char	*key;
	char	*current_value;

	i = 0;
	while (arg[i] && arg[i] != '+')
		i++;
	if (!(key = ft_strndup(arg, i)))
		return (NULL);
	i += 2;
	if (!(current_value = get_env(key)))
	{
		if (!(current_value = ft_strdup(&arg[i])))
			return (NULL);
	}
	else if (!(current_value = ft_strjoin_2free(current_value,
				ft_strdup(&arg[i]))))
		return (NULL);
	if (!(key = ft_strjoin_free(key, "=")))
		return (NULL);
	if (!(current_value = ft_strjoin_2free(key, current_value)))
		return (NULL);
	free(arg);
	return (current_value);
}
