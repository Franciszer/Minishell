/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 13:58:47 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/10 13:59:19 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			export_envvar(int i, char **argv)
{
	char	*var;
	int		syntax_check;
	int		return_value;
	char	*to_free;

	if ((syntax_check = export_check_syntax(argv[i])) == 1)
		return (1);
	if (syntax_check == 3 && !(argv[i] = added_var(argv[i])))
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
