/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 10:06:24 by franciszer        #+#    #+#             */
/*   Updated: 2020/06/29 14:58:00 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_exit(t_list *token_list)
{
	char	*token;

	if (!token_list)
		return (0);
	token = (char*)token_list->content;
	if ((!ft_strncmp(token, "exit", (ft_strlen("exit") + 1)) ||
		!ft_strncmp(token, "\"exit\"", (ft_strlen("\"exit\"") + 1)) ||
		!ft_strncmp(token, "\'exit\'", (ft_strlen("\'exit\'") + 1))))
		return (1);
	return (0);
}
