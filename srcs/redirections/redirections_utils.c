/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:28:06 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/08 15:40:12 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				is_redir(char *cmd)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (cmd_len == 2)
	{
		if (!ft_strncmp(cmd, ">>", 3))
			return (1);
	}
	else if (cmd_len == 1)
	{
		if (!ft_strncmp(cmd, ">", 2))
			return (2);
		else if (!ft_strncmp(cmd, "<", 2))
			return (3);
	}
	return (0);
}

int				is_dir(t_redirection redir)
{
	struct stat		path_stat;
	char			*tmp;

	stat(redir.file, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		tmp = ft_strjoin(ERR_REDIR_IS_DIR_P1, redir.file);
		tmp = ft_strjoin_free(tmp, ERR_REDIR_IS_DIR_P2);
		g_exit_status = 1;
		ft_perror(tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

int				file_not_found(t_redirection redir)
{
	char			*tmp;

	tmp = ft_strjoin(ERR_REDIR_DONT_FIND_P1, redir.file);
	tmp = ft_strjoin_free(tmp, ERR_REDIR_DONT_FIND_P2);
	g_exit_status = 2;
	ft_perror(tmp);
	free(tmp);
	return (1);
}

t_redirection	stock_redir(char **argv)
{
	int				i;
	t_redirection	redir;
	int				type;

	i = -1;
	redir.putfile = 0;
	redir.putendfile = 0;
	redir.in = 0;
	redir.file = 0;
	while (argv[++i])
	{
		if ((type = is_redir(argv[i])))
		{
			if (type == 1)
				redir.putendfile = 1;
			else if (type == 2)
				redir.putfile = 1;
			else if (type == 3)
				redir.in = 1;
			if (argv[i + 1])
				redir.file = ft_strdup(argv[i + 1]);
			return (redir);
		}
	}
	return (redir);
}

void			cmd_to_rafter(char ***cmd)
{
	int		i;
	int		type;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	while ((*cmd)[i])
	{
		if ((type = is_redir((*cmd)[i])))
		{
			tmp1 = (*cmd)[i];
			tmp2 = (*cmd)[i + 1];
			while ((*cmd)[i + 2])
			{
				(*cmd)[i] = (*cmd)[i + 2];
				i++;
			}
			(*cmd)[i] = NULL;
			free(tmp1);
			free(tmp2);
			break ;
		}
		i++;
	}
}
