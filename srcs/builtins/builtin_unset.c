/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 11:40:02 by franciszer        #+#    #+#             */
/*   Updated: 2020/07/21 19:10:29 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*strndup_len_char(const char *s, char c)
{
	return (ft_strndup(s, ft_strlen_char(s, c)));
}

int			remove_var_loop(char *var_name, t_list *nav, t_list *prev,
						t_list **env_list)
{
	t_list	*to_free;
	char	*tmp;

	while (nav)
	{
		if (!(tmp = strndup_len_char((char*)nav->content, '=')))
			return (1);
		if (!ft_strncmp(var_name, tmp, ft_strlen(tmp)))
		{
			to_free = nav;
			nav = nav->next;
			ft_lstdelone(to_free, free);
			if (!prev)
				*env_list = nav;
			else
				prev->next = nav;
		}
		else
		{
			prev = nav;
			nav = nav->next;
		}
		free(tmp);
	}
	return (0);
}

int			remove_var(char *var_name)
{
	t_list	*env_list;
	t_list	*nav;
	t_list	*prev;

	if (!(env_list = ft_argv_to_list(g_env)))
		return (1);
	nav = env_list;
	prev = NULL;
	if (remove_var_loop(var_name, nav, prev, &env_list))
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

int			builtin_unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		remove_var(argv[i]);
		i++;
	}
	return (0);
}
