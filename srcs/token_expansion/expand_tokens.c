/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 11:57:50 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/02 11:46:30 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_token_noquote(char *token, char **env)
{
	int		i;
	int		j;
	int		prev_is_backslash;
	char	*final_token;
	

	i = 0;
	j = 0;
	prev_is_backslash = 0;
	if (!(final_token = (char*)malloc(sizeof(char) * 100)))
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
			else if (token[i] == '$' && token[i + 1] && ft_isalnum(token[i + 1]))
			{
				if (!(final_token = expand_env(token, &i, &j, env)))
					return (NULL);
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

char	*expand_token_dquote(char *token, char **env)
{
	int		i;
	int		j;
	int		prev_is_backslash;
	char	*final_token;
	

	i = 0;
	j = 0;
	prev_is_backslash = 0;
	if (!(final_token = (char*)malloc(sizeof(char) * ft_strlen_etokens(token, env))))
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
			else if (token[i] == '$' && token[i + 1] && ft_isalnum(token[i + 1]))
			{
				if (!(final_token = expand_env(token, &i, &j, env)))
					return (NULL);
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
	final_token[j] = '\0';
	return (final_token);
}

void	*get_final_token(void *content, void *env)
{
	char	*str;

	if (((char*)content)[0] == '\"')
	{
		str = ((char*)content);
		str = remove_quotes_free(str, '\"');
		str = expand_token_dquote(str, (char**)env);
	}
	else if (((char*)content)[0] == '\'')
	{
		str = ((char*)content);
		str = remove_quotes_free(str, '\'');
	}
	else
		str = expand_token_noquote((char*)content, (char**)env);
	if (str[0] == '\0')
	{
		//free(content);
		return (NULL);
	}
	else
		return (str);
}

t_list	*expand_tokens(t_list **token_list, char **env)
{
	t_list	*expanded_list;

	if (!(expanded_list = ft_lstfilter_data(token_list, get_final_token, free, (void*)env)))
		return (NULL);
	ft_lstclear(token_list, free);
	return (expanded_list);
}
