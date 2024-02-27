/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_route.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:14:45 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/27 15:44:32 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	msg_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

static void	child(int *fd, t_data *data)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		msg_error("Child read error\n");
	if (dup2(data->file2, STDOUT_FILENO) == -1)
		msg_error("Child wrt error\n");
	if (execve(data->route[1], data->cmd[1], NULL) == -1)
		msg_error("Child exec error\n");
	close(data->file2);
}

void	exec_route(t_data *data)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		msg_error("Pipe error\n");
	pid = fork();
	if (pid == -1)
		msg_error("Fork error\n");
	if (pid == 0)
		child(fd, data);
	else
	{
		close(fd[0]);
		if (dup2(data->file1, STDIN_FILENO) == -1)
			msg_error("Read error\n");
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			msg_error("Wrt error\n");
		close(data->file1);
		if (execve(data->route[0], data->cmd[0], NULL) == -1)
			msg_error("Exec error\n");
		waitpid(pid, NULL, 0);
	}
}
