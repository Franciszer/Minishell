/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:48:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/11 14:30:31 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*last_token(t_list *token_list)
{
	t_list	*nav;

	nav = token_list;
	while (nav)
	{
		if (!nav->next)
			return (char*)nav->content;
		nav = nav->next;
	}
	return (NULL);
}

int		ft_is_sep(char *s)
{
	if (!ft_strncmp(s, "|", 2) ||\
	!ft_strncmp(s, ";", 2))
		return (1);
	return (0);
}

int		check_pipe_error(t_list *token_list)
{
	t_list	*tmp;
	int		prev_is_sep;

	prev_is_sep = 0;
	if (ft_is_sep(first_token(token_list)))
		return (1);
	tmp = token_list;
	while (tmp)
	{
		if (ft_is_sep(tmp->content))
		{
			if (prev_is_sep)
				return (g_pipe_error = 1);
			else
				prev_is_sep = 1;
		}
		else
			prev_is_sep = 0;
		tmp = tmp->next;
	}
	return (0);
}

int		check_semicol_error(t_list *token_list)
{
	t_list	*tmp;
	int		prev_is_semicol;

	prev_is_semicol = 0;
	if (!ft_strncmp(first_token(token_list), ";", 2))
		return (1);
	tmp = token_list;
	while (tmp)
	{
		if (!ft_strncmp((char*)tmp->content, ";", 2))
		{
			if (prev_is_semicol)
				return (g_semicol_error = 1);
			else
				prev_is_semicol = 1;
		}
		else
			prev_is_semicol = 0;
		tmp = tmp->next;
	}
	return (0);
}

t_list	*prompt_loop(int depth)
{
	char	*line;
	t_list	*token_list;
	int		ret_value;

	g_p_stop_sig = 0;
	if ((ret_value = get_next_line(STDIN_FILENO, &line)) < 0)
	{
		if (ret_value != -2)
			ft_perror(ERR_READLINE);
		exit(0);
		return (NULL);
	}
	token_list = tokenize(line);
	free(line);
	if (check_pipe_error(token_list) || check_semicol_error(token_list))
	{
		g_exit_status = 2;
		ft_lstclear(&token_list, free);
		return (ft_perror(ERR_PIPE) == 0 ? NULL : NULL);
	}
	else if ((!ft_strncmp(last_token(token_list), "|", 2))
		|| (depth >= 1 && !last_token(token_list)))
		return (pipe_handle(depth, &token_list));
	return (token_list);
}
