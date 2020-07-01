/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 12:40:14 by frthierr          #+#    #+#             */
/*   Updated: 2020/06/29 13:36:11 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*init_commands()
{
	t_commands	*commands;

	if (!(commands = (t_commands*)malloc(sizeof(t_commands))))
		return (NULL);
	if (!(commands->command_names = init_command_names()))
		return (NULL);
	if (!(commands->command_paths = init_command_paths()))
		return (NULL);
	return (commands);	
}

char	**init_command_names()
{
	int		i;
	char	**command_names;

	i = 0;
	if (!(command_names = (char**)malloc(sizeof(char*) * (NB_COMMANDS + 1))))
		return (NULL);
	command_names[NB_COMMANDS] = NULL;
	if (!(command_names[0] = ft_strdup(COMMAND0_NAME)))
		return (NULL);
	return (command_names);
}

char	**init_command_paths()
{
	int		i;
	char	**command_paths;

	i = 0;
	if (!(command_paths = (char**)malloc(sizeof(char*) * (NB_COMMANDS + 1))))
		return (NULL);
	command_paths[NB_COMMANDS] = NULL;
	if (!(command_paths[0] = ft_strdup(COMMAND0_PATH)))
		return (NULL);
	return (command_paths);
}

int		get_command_index(char *command, t_commands *commands)
{
	int		i;

	i = 0;
	while (commands->command_names[i])
	{
		if (!ft_strncmp(command, commands->command_names[i], (ft_strlen(commands->command_names[i]) + 1)))
			return (i);
		i++;
	}
	return (-1);
}

int		free_commands(t_commands *commands)
{
	free_argv(commands->command_names, INT_MAX);
	free_argv(commands->command_paths, INT_MAX);
	free(commands);
	return (1);
}
