/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 14:37:03 by franciszer        #+#    #+#             */
/*   Updated: 2020/06/29 13:34:57 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_launch(char **argv)
{
	t_commands	*commands;
	int			index;

	if (!(commands = init_commands()))
		return (0);
	if ((index = get_command_index(argv[0], commands)) >= 0)
	{
		if ((execve((const char*)commands->command_paths[index], NULL, NULL)) == -1)
			ft_printf("ERROR\n");
	}
	else
		ft_perror(ERR_UNKNOWN_COMMAND);
	free_commands(commands);
	return (1);
}