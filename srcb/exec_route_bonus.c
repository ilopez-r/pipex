/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_route_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:20:41 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/29 19:52:38 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	msg_error(char *str)
{
	unlink("here_doc.tmp");
	perror(str);
	exit(EXIT_FAILURE);
}

void	here_doc(t_data *data, char **argv, char *line)
{
	data->file1 = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->file1 < 0)
		return ;
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			msg_error("Get_next_line error");
		if (!ft_strncmp(argv[2], line, ft_strlen(argv[2])))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, data->file1);
		free(line);
	}
	close(data->file1);
	data->file1 = open("here_doc.tmp", O_RDONLY);
	if (data->file1 == -1)
		msg_error("Here_doc open file1 error");
}

void	executer(t_data *data, pid_t pid, int j)
{
	int		fd[2];

	while (data->route[(++j) + 1] != NULL)
	{
		if (pipe(fd) == -1)
			msg_error("Pipe error\n");
		pid = fork();
		if (pid == -1)
			msg_error("Fork error\n");
		if (pid == 0)
		{
			close(fd[0]);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				msg_error("Wrt error\n");
			if (execve(data->route[j], data->cmd[j], NULL) == -1)
				msg_error("Exec error\n");
		}
		else
		{
			waitpid(pid, NULL, 0);
			close (fd[1]);
			if (dup2(fd[0], STDIN_FILENO) == -1)
				msg_error("Read error\n");
		}
	}
}

void	exec_route_bonus(t_data *d, char **argv, int argc, int flag)
{
	if (flag == 1)
	{
		here_doc (d, argv, NULL);
		if (dup2(d->file1, STDIN_FILENO) == -1)
			msg_error("Here_doc read error\n");
		d->file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		unlink("here_doc.tmp");
	}
	else
	{
		d->file1 = open(argv[1], O_RDONLY);
		if (d->file1 == -1)
			msg_error("Open file1 error");
		if (dup2(d->file1, STDIN_FILENO) == -1)
			msg_error("File1 read error \n");
		d->file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	executer(d, 0, -1);
	if (dup2(d->file2, STDOUT_FILENO) == -1)
		msg_error("File2 wrt error\n");
	if (execve(d->route[argc - 4 - flag], d->cmd[argc - 4 - flag], NULL) == -1)
		msg_error("Last command exec error\n");
}
