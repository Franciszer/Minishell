/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 13:58:47 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/22 12:55:02 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			replace_envvar(char *arg)
{
	t_list	*env_list;
	t_list	*nav;
	char	*current_env;
	size_t	len;
	int		replaced;

	if (!ft_strchr(arg, '=') && (current_env = get_env(arg)))
	{
		free(current_env);
		return (1);
	}
	if (!(env_list = ft_argv_to_list(g_env)))
		return (0);
	replaced = 0;
	if (g_env_modified)
		free_argv(g_env, INT_MAX); 
	g_env_modified = 1;
	nav = env_list;
	while (nav && !replaced)
	{
		current_env = (char*)nav->content;
		len = ft_strlen(current_env);
		if (current_env[len - 1] != '=' && !ft_strncmp(current_env, arg, ft_strlen(current_env)))
		{
			free(nav->content);
			if (!(nav->content = ft_strdup(arg)))
				return (0);
			replaced = 1;
		}
		nav = nav->next;
	}
	if (!(g_env = list_to_argv(env_list)))
		return (0);
	ft_lstclear(&env_list, free);
	if (replaced)
		return (1);
	return (0);
}

int			export_envvar(int i, char **argv)
{
	char	*var;
	int		syntax_check;
	int		return_value;
	char	*to_free;

	if (replace_envvar(argv[i]))
		return (0);
	if ((syntax_check = export_check_syntax(argv[i])) == 1)
		return (1);
	if (syntax_check == 3 && !(argv[i] = added_var(argv[i])))
		return (1);
	if (syntax_check == 2)
		return (return_value = new_env_var(argv[i]));
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

int			all_env_written(char *env_written, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (!env_written[i++])
			return (0);
	}
	return (1);
}
