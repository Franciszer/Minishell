/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:41:59 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/04 19:47:39 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*path;

	path = search_path("ls", env);
	printf("%s\n", path);
	free(path);
}
