/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 10:36:09 by franciszer        #+#    #+#             */
/*   Updated: 2020/08/09 18:34:19 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_list *tokenlist)
{
	t_list	*nav;

	nav = tokenlist;
	while (nav)
	{
		ft_printf("[%s]\n", (char*)nav->content);
		nav = nav->next;
	}
}

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		ft_printf("%d: |%s|\n", i, argv[i]);
		i++;
	}
}
