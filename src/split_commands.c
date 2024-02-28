/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:25:32 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/27 15:35:34 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free_pipex(char **str, int i)
{
	while (i-- > 0)
		free(str[i]);
	free(str);
}

static int	ft_counter_pipex(char const *s, char c)
{
	int		count;
	int		flag;

	count = 0;
	flag = 0;
	while (*s != '\0')
	{
		while ((*s == c || *s == '\'' || *s == '\"') && *s != '\0')
		{
			if (*s == '\'' || *s == '\"')
				flag = !flag;
			s++;
		}
		count++;
		if (flag)
		{
			while (*s != '\'' && *s != '\"' && *s != '\0')
				s++;
			flag = !flag;
		}
		while (*s != c && *s != '\0')
			s++;
	}
	return (count);
}

static int	ft_len_pipex(char const *s, char c, int *d)
{
	int	len;
	int	flag;

	len = 0;
	flag = 0;
	while (s[*d] != '\0' && s[*d] != c)
	{
		while ((s[*d] == '\'' || s[*d] == '\"') && s[*d] != '\0')
		{
			flag = !flag;
			(*d)++;
			if (s[*d] == c || s[*d] == '\0')
				flag = !flag;
			if (flag && (s[*d] == c || s[*d] == '\0'))
				return ((*d)--, len);
			if (s[*d] == c)
				(*d)++;
		}
		while ((flag || s[*d] != c) && s[*d] != '\'' && s[*d] != '\"')
		{
			(*d)++;
			len++;
		}
	}
	return (len);
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**str;
	int		i;
	int		d;
	int		len;

	d = 0;
	i = -1;
	str = malloc((ft_counter_pipex (s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (++i < ft_counter_pipex (s, c))
	{
		len = ft_len_pipex(s, c, &d);
		str[i] = ft_substr(s, (d - len), len);
		while (s[d] == c)
			d++;
		if (!(str[i]))
		{
			ft_free_pipex(str, i);
			return (0);
		}
	}
	str[i] = NULL;
	return (str);
}

int	split_commands(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	data->cmd = ft_calloc((argc - 3) + 1, sizeof(char **));
	if (!data->cmd)
		return (EXIT_FAILURE);
	while (i < argc - 3)
	{
		data->cmd[i] = ft_split_pipex (argv[j], ' ');
		if (!data->cmd[i])
			return (EXIT_FAILURE);
		i++;
		j++;
	}
	data->cmd[i] = NULL;
	return (EXIT_SUCCESS);
}
