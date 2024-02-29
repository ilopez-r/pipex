/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:22:39 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/29 19:52:24 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*void	ft_leaks(void)
{
	system("leaks -q pipex_bonus");
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

int	check_arguments(char *argv, int *flag_doc)
{
	if (ft_strncmp(argv, "here_doc", 8) == 0)
		return (*flag_doc = 1, 6);
	return (5);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		i;
	int		flag_doc;

	i = 1;
	flag_doc = 0;
	if (argc < check_arguments(argv[1], &flag_doc))
		return (ft_printf("Number of arguments error"), EXIT_FAILURE);
	if (flag_doc == 1)
		i++;
	while (++i <= argc - 2)
		if (argv[i][0] == '\0')
			return (ft_printf ("Read arguments error\n"), EXIT_FAILURE);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	init_struct(data);
	if (split_commands_bonus(argc, argv, data, flag_doc) == 1)
		return (ft_printf ("Commands error\n"), free_all (data), EXIT_FAILURE);
	if (split_path_bonus(env, data) == 1)
		return (ft_printf ("Path error\n"), free_all (data), EXIT_FAILURE);
	if (get_route_bonus(data, argc - 3, -1, 0) == 1)
		return (ft_printf ("Route error\n"), free_all (data), EXIT_FAILURE);
	exec_route_bonus(data, argv, argc, flag_doc);
	return (free_all(data), EXIT_SUCCESS);
}
