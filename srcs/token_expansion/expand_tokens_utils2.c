/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 16:53:56 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/25 15:06:24 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_token(char **tk, int check_quote)
{
	if ((!(*tk) || !(*tk)[0]) && check_quote)
	{
		if (*tk)
			free(*tk);
		return (ft_strdup("\33\127"));
	}
	return (*tk);
}