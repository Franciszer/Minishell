/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:25:27 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/24 12:27:44 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_quote_string(char *str)
{
	char	*qstr;
	int		i;

	i = 0;
	if (!(qstr = malloc(sizeof(char) * (ft_strlen(str) + 3))))
		return (NULL);
	qstr[0] = '\"';
	while (str[i++])
		qstr[i] = str[i - 1];
	qstr[i++] = '\"';
	qstr[i] = '\0';
	return (qstr);
}

char		*ft_quote_envvar(char *envvar)
{
	char	*head;
	char	*tail;
	char	*tmp;
	int		i;

	i = 0;
	if (!(head = malloc(sizeof(char) * (ft_strlen(envvar) + 2))))
		return (NULL);
	while (envvar[i] && envvar[i] != '=')
	{
		head[i] = envvar[i];
		i++;
	}
	if (!envvar[i])
		return ((head = ft_strndup_free(envvar, ft_strlen_char(envvar, '='))));
	head[i++] = '=';
	head[i] = 0;
	if (!(tmp = ft_strdup(&envvar[i])))
		return (NULL);
	if (!(tail = ft_quote_string(tmp)))
		return (NULL);
	free(tmp);
	if (!(head = ft_strjoin_2free(head, tail)))
		return (NULL);
	return (head);
}

void		print_export_loop(char **env_written, size_t len)
{
	size_t	lowest_index;
	size_t	i;
	char	*quoted_string;

	while (!all_env_written(*env_written, len))
	{
		lowest_index = 0;
		while ((*env_written)[lowest_index])
			lowest_index++;
		i = 1;
		while (g_env[i])
		{
			if (!(*env_written)[i] && ft_strncmp(g_env[lowest_index],
							g_env[i], ft_strlen(g_env[lowest_index]) + 1) > 0)
				lowest_index = i;
			i++;
		}
		(*env_written)[lowest_index] = 1;
		if (!(quoted_string = ft_quote_envvar(g_env[lowest_index])))
			return ;
		ft_printf("declare -x %s\n", quoted_string);
		free(quoted_string);
	}
}

int			print_export(void)
{
	size_t	len;
	char	*env_written;

	len = 0;
	while (g_env[len])
		len++;
	if (!(env_written = (char*)malloc(sizeof(char) * (len))))
		return (1);
	ft_bzero(env_written, len);
	print_export_loop(&env_written, len);
	free(env_written);
	return (0);
}

int			builtin_export(char **argv)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!argv[1])
		return (print_export());
	while (argv[i])
	{
		if (export_envvar(i, argv))
			status = 1;
		i++;
	}
	return (status);
}
