/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:36:26 by frthierr          #+#    #+#             */
/*   Updated: 2020/06/25 12:21:31 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t maxsize)
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
	return (str);
}
