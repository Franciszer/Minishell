/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 13:58:47 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/24 15:22:48 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			replace_envvar_util(t_list *nav, char *arg)
{
	char	*current_env;
	size_t	len;

	current_env = (char*)nav->content;
	len = ft_strlen(current_env);
	if (current_env[len - 1] != '=' &&\
		!ft_strncmp(current_env, arg, ft_strlen(current_env)))
	{
		free(nav->content);
		if (!(nav->content = ft_strdup(arg)))
			return (-1);
		return (1);
	}
	return (0);
}

int			replace_envar_free(t_list **env_list, char *new_arg, int replaced)
{
	if (!(g_env = list_to_argv(*env_list)))
		return (0);
	ft_lstclear(env_list, free);
	free(new_arg);
	if (replaced)
		return (1);
	return (0);
}

int			replace_envvar(char *arg)
{
	t_list	*env_list;
	t_list	*nav;
	char	*current_env;
	int		replaced;
	char	*new_arg;

	if (!ft_strchr(arg, '=') && (current_env = get_env(arg, 0)))
	{
		free(current_env);
		return (1);
	}
	if (!(new_arg = remove_plus_sign(arg)))
		return (0);
	if (!(env_list = replance_envvar_init_vals(&replaced)))
		return (0);
	nav = env_list;
	while (nav && !replaced)
	{
		if ((replaced = replace_envvar_util(nav, new_arg)) == -1)
			return (0);
		nav = nav->next;
	}
	return (replace_envar_free(&env_list, new_arg, replaced));
}

int			export_envvar(int i, char **argv)
{
	char	*var;
	int		syntax_check;
	int		return_value;
	char	*to_free;

	return_value = 0;
	if (replace_envvar(argv[i]))
		return (0);
	if ((syntax_check = export_check_syntax(argv[i])) == 1)
		return (!ft_perror("invalid argument") ? 1 : 1);
	if (syntax_check == 3 && (argv[i] = added_var(argv[i])))
		return (0);
	if (syntax_check == 2)
		return (return_value = new_env_var(argv[i]));
	if (!(var = ft_strndup(argv[i], ft_strlen_char(argv[i], '='))))
		return (1);
	if (!(to_free = get_env(var, 0)))
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
