/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 11:57:50 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/06 20:36:44 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_token_noquote(char *token)
{
	int		i;
	int		j;
	int		prev_is_backslash;
	char	*final_token;
	char	*tmp;
	

	i = 0;
	j = 0;
	prev_is_backslash = 0;
	if (!(final_token = (char*)malloc(sizeof(char) * ft_strlen_etokens(token))))
		return (NULL);
	while (token[i])
	{
		if (!prev_is_backslash)
		{
			if (token[i] == '\\')
			{
				prev_is_backslash = 1;
				i++;
			}
			else if (token[i] == '$' && token[i + 1] && (ft_isalnum(token[i + 1]) || token[i + 1] == '?'))
			{
				tmp = final_token;
				if (!(final_token = expand_env(token, final_token, &i, &j)))
					return (NULL);
				free(tmp);
				if (!final_token)
					return(ft_strdup(""));
				if (!final_token[0])
				{
					return (final_token);
				}
			}
			else
			{
				final_token[j] = token[i];
				j++;
				i++;
			}
		}
		else
		{
			prev_is_backslash = 0;
			final_token[j] = token[i];
			j++;
			i++;
		}
	}
	final_token[j] = '\0';
	return (final_token);
}

char	*expand_token_dquote(char *token)
{
	int		i;
	int		j;
	int		prev_is_backslash;
	char	*final_token;
	char	*tmp;
	

	i = 0;
	j = 0;
	prev_is_backslash = 0;
	if (!(final_token = (char*)malloc(sizeof(char) * ft_strlen_etokens(token))))
		return (NULL);
	while (token[i])
	{
		if (!prev_is_backslash)
		{
			if (token[i] == '\\' && token[i + 1])
			{
				prev_is_backslash = 1;
				i++;
			}
			else if (token[i] == '$' && token[i + 1] && (ft_isalnum(token[i + 1]) || token[i + 1] == '?'))
			{
				tmp = final_token;
				if (!(final_token = expand_env(token, final_token, &i, &j)))
					return (NULL);
				free(tmp);
				if (!final_token)
					return(ft_strdup(""));
				if (!final_token[0])
				{
					free(token);
					return (final_token);
				}
			}
			else
			{
				final_token[j] = token[i];
				j++;
				i++;
			}
		}
		else
		{
			prev_is_backslash = 0;
			if (!is_specialchar_dquote(token[i]))
				final_token[j++] = '\\';
			final_token[j] = token[i];
			j++;
			i++;
		}
	}
	free(token);
	final_token[j] = '\0';
	return (final_token);
}

void	*get_final_token(void *content)
{
	char	*str;

	if (((char*)content)[0] == '\"')
	{
		str = ((char*)content);
		str = remove_quotes_free(str, '\"');
		str = expand_token_dquote(str);
	}
	else if (((char*)content)[0] == '\'')
	{
		str = ((char*)content);
		str = remove_quotes_free(str, '\'');
	}
	else
	{
		str = expand_token_noquote((char*)content);
		if (str[0] == '\0')
		{
			free(str);
			return (NULL);
		}	
	}
	return (str);
}

t_list	*expand_tokens(t_list *token_list)
{
	t_list	*expanded_list;
	t_list	*tmp_list;
	
	tmp_list = token_list;
	expanded_list = ft_lstfilter(&tmp_list, get_final_token, free);
	return (expanded_list);
}
