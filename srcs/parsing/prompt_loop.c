/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:48:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/06 18:13:21 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt()
{
	g_p_stop_sig = 0;
	write(1, LIGHT_BLUE, ft_strlen(LIGHT_BLUE));
	write(1, PROMPT_START_MSG, ft_strlen(PROMPT_START_MSG));
	write(1, NC, ft_strlen(NC));
}

t_list *prompt_loop()
{
	char *line;
	t_list *tokenList;

	if (get_next_line(STDIN_FILENO, &line) < 0)
	{
		ft_perror(ERR_READLINE);
		return (NULL);
	}
	tokenList = tokenize(line);
	free(line);
	return (tokenList);
}
