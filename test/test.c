/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:41:59 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/01 16:26:16 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	 char *str;

	str = ft_strdup("\"\"");
 	printf("%s|\n", str);
	printf("%s|\n", remove_quotes_free(str, '\"'));
}
