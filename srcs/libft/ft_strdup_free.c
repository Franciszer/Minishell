/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:22:56 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/01 11:23:29 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(char *s)
{
	char	*n;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (!(n = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		n[i] = s[i];
		i++;
	}
	n[i] = '\0';
	free(s);
	return (n);
}