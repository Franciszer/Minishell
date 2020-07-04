/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:25:27 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/04 10:36:01 by franciszer       ###   ########.fr       */
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
	ft_lstadd_back(&env_list, new);
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

static void	*is_env_var(void *content, void *str)
{
	char	*key;

	if (!(key = ft_strndup((char*)str, ft_strlen_char((char*)str, '=') + 1)))
		return (NULL);
	if (!ft_strncmp((const char*)content, key, ft_strlen(key) + 1))
		return (NULL);
	else
		return ((void*)ft_strdup((const char*)content));
}

int		modify_env_var(int index, char **argv, char **env)
{
	t_list	*env_list;
	t_list	*filtered_env_list;
	t_list	*new;
	char	*new_var;

	if (!(env_list = ft_argv_to_list(env)))
		return (1);
	if (!(filtered_env_list = ft_lstfilter_data(&env_list, is_env_var, free, (void*)argv[index])))
		return (1);
	if (!(new_var = ft_strdup(argv[index])))
		return (1);
	if (!(new = ft_lstnew(new_var)))
		return (1);
	ft_lstadd_back(&filtered_env_list, new);
	// free_argv(env, INT_MAX);
	if (!(env = list_to_argv(filtered_env_list)))
		return (NULL);
	return (env);
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
		modify_env_var(i, argv, env);
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
