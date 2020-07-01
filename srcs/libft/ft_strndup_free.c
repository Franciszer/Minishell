/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:25:21 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/01 11:25:54 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup_free(char *s, size_t maxsize)
{
	char	*str;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	size = ft_strlen(s) > maxsize ? maxsize : ft_strlen(s);
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = s[i];
		maxsize--;
		i++;
	}
	str[i] = '\0';
	free(s);
	return (str);
}
