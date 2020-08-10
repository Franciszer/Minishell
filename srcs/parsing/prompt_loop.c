/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:48:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/10 14:22:10 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*pipe_handle(int depth, t_list **token_list)
{
	t_list	*tmp;

	if (depth == 0)
		g_open_pipe = 1;
	print_prompt();
	tmp = prompt_loop(depth + 1);
	ft_lstadd_back(token_list, tmp);
	if (depth == 0)
		g_open_pipe = 0;
	return ((*token_list));
}

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

int		check_pipe_error(t_list *token_list)
{
	t_list	*tmp;
	int		prev_is_pipe;

	prev_is_pipe = 0;
	if (!ft_strncmp(first_token(token_list), "|", 2))
		return (1);
	tmp = token_list;
	while (tmp)
	{
		if (!ft_strncmp((char*)tmp->content, "|", 2))
		{
			if (prev_is_pipe)
				return (g_pipe_error = 1);
			else
				prev_is_pipe = 1;
		}
		else
			prev_is_pipe = 0;
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
		return (token_list);
	else if ((!ft_strncmp(last_token(token_list), "|", 2))
		|| (depth >= 1 && !last_token(token_list)))
		return (pipe_handle(depth, &token_list));
	return (token_list);
}
