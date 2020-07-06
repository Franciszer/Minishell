/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:41:59 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/06 12:13:41 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	all_env_written(char *env_written, size_t len)
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

static int	print_export()
{
	size_t	len;
	size_t	i;
	size_t	lowest_index;
	char	*env_written;

	len = 0;
	while (g_env[len])
		len++;
	if (!(env_written = (char*)malloc(sizeof(char) * (len))))
		return (1);
	ft_bzero(env_written, len);
	while (!all_env_written(env_written, len))
	{
		lowest_index = 0;
		while (env_written[lowest_index])
			lowest_index++;
		i = 1;
		while (g_env[i])
		{
			if (!env_written[i] && ft_strncmp(g_env[lowest_index], g_env[i], ft_strlen(g_env[lowest_index]) + 1) > 0)
				lowest_index = i;
			i++;
		}
		env_written[lowest_index] = 1;
		ft_printf("declare -x %s\n", g_env[lowest_index]);
	}
	free(env_written);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char **args;
	
	g_env = env;
	print_export();
	system("leaks test_exec");
}
