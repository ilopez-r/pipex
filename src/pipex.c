/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:24:10 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/27 16:07:48 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*void	ft_leaks(void)
{
	system("leaks -q pipex");

	copiar esta: atexit(ft_leaks);
}*/

void	free_all(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	if (d->cmd == NULL && d->path == NULL && d->route == NULL)
		return (free(d));
	while (d->cmd[i] != NULL || d->path[i] != NULL || d->route[i] != NULL)
	{
		if (d->cmd[i] != NULL)
		{
			j = -1;
			while (d->cmd[i][++j] != NULL)
				free(d->cmd[i][j]);
			free(d->cmd[i]);
		}
		if (d->path[i] != NULL)
			free(d->path[i]);
		if (d->route[i] != NULL)
			free(d->route[i]);
		i++;
	}
	free(d->cmd);
	free(d->path);
	free(d->route);
	free(d);
}

static void	init_struct(t_data *data)
{
	data->file1 = 0;
	data->file2 = 0;
	data->path = NULL;
	data->cmd = NULL;
	data->route = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	
	if (argc != 5 || argv[1][0] == '\0' || argv[2][0] == '\0')
		return (ft_printf ("Arguments error\n"), EXIT_FAILURE);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	init_struct(data);
	data->file1 = open(argv[1], O_RDONLY);
	if (data->file1 == -1)
		return (ft_printf("Open file error\n"), free_all (data), EXIT_FAILURE);
	data->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (split_commands(argc, argv, data) == 1)
		return (ft_printf ("Commands error\n"), free_all (data), EXIT_FAILURE);
	if (split_path(env, data) == 1)
		return (ft_printf ("Path error\n"), free_all (data), EXIT_FAILURE);
	if (get_route(data, argc - 3, -1, 0) == 1)
		return (ft_printf ("Route error\n"), free_all (data), EXIT_FAILURE);
	exec_route(data);
	return (EXIT_SUCCESS);
}
