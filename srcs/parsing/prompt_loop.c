/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:48:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/02 14:48:40 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *prompt_loop()
{
	char *line;
	t_list *tokenList;

	write(1, LIGHT_BLUE, ft_strlen(LIGHT_BLUE));
	write(1, PROMPT_START_MSG, ft_strlen(PROMPT_START_MSG));
	write(1, NC, ft_strlen(NC));
	if (get_next_line(STDIN_FILENO, &line) < 0)
	{
		ft_perror(ERR_READLINE);
		return (NULL);
	}
	tokenList = tokenize(line);
	free(line);
	return (tokenList);
}
