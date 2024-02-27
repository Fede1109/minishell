/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:31:03 by fdiaz-gu          #+#    #+#             */
/*   Updated: 2024/02/27 13:04:37 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	ft_fork(t_tools *tools, int pipe_fd[2], int fd_in, t_simple_cmds *parser)
{
	static int i = 0;
	tools->pid[i] = fork();
	if (tools->pid[i] < 0)
	{
		perror("pid_fork");
		return (EXIT_FAILURE);
	}
	if (tools->pid[i] == 0)
		handle_dup(parser, tools, pipe_fd, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

t_simple_cmds	*ft_simple_cmdsfirst(t_simple_cmds *map)
{
	if (!map)
		return (NULL);
	while (map->prev != NULL)
		map = map->prev;
	return (map);
}

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	return (EXIT_SUCCESS);
}


void	execute_one(t_tools *tools)
{
	int	exit_code;

	exit_code = 0;
	if (tools->parser->redirections > 0)
		if (handle_redirects(tools->parser->redirections))
			exit(1);
	if (tools->parser->builtin)
	{
		exit_code = tools->parser->builtin(tools, tools->parser);
		exit(exit_code);
	}
	else if (tools->parser->str[0][0])
		exit_code = exec_cmd(tools);
	exit(exit_code);
}
