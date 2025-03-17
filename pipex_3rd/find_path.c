/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:54:13 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/17 14:04:38 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command_if_valid(t_pipex *pipex, char **commands,
		const char *envp[], char *full_path)
{
	if (!full_path)
	{
		ft_putstr_fd ("path not found", 2);
		clean_and_exit (pipex, commands);
	}
	if (access(full_path, F_OK | X_OK) == 0)
	{
		close (pipex->outfile);
		close (pipex->infile);
		if (execve(full_path, commands, (char *const *)envp) == -1)
		{
			free (full_path);
			clean_and_exit (pipex, commands);
		}
	}
}

void	find_path(t_pipex *pipex, const char *envp[], int *fd)
{
	int	i;

	i = 0;
	pipex->path = NULL;
	if (!envp || envp[0] == NULL)
	{
		pipex->path = ft_strdup("/usr/bin:/bin:/usr/sbin:/sbin");
		if (!pipex->path)
			print_error(ERR_W);
	}
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			pipex->path = ft_strdup(&envp[i][5]);
			break ;
		}
		i++;
	}
	if (!pipex->path)
	{
		ft_putstr_fd ("command not found\n", 2);
		ft_putstr_fd ("command not found\n", 2);
		close(pipex->infile);
		close(pipex->outfile);
		close(fd[0]);
		close(fd[1]);
		exit(127);
	}
}

void	split_path(t_pipex *pipex, char **commands, const char *envp[])
{
	int		i;
	char	*temp_path;
	char	*full_path;

	pipex->paths = ft_split(pipex->path, ':');
	if (!pipex->paths)
		clean_and_exit(pipex, commands);
	i = 0;
	while (pipex->paths[i] != NULL)
	{
		temp_path = ft_strjoin(pipex->paths[i], "/");
		full_path = ft_strjoin(temp_path, commands[0]);
		free(temp_path);
		execute_command_if_valid(pipex, commands, envp, full_path);
		free(full_path);
		i++;
	}
	clean_and_exit(pipex, commands);
}
