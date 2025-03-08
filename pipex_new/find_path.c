/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:54:13 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/08 09:23:59 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup_pipex(t_pipex *pipex, char **commands)
{
	free_string(pipex->paths);
	free_string(commands);
}

void	close_and_wait(t_pipex *pipex, int *fd)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	close(pipex->infile);
	close(pipex->outfile);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(1);
}

void	print_error(char *str)
{
	perror(str);
	exit(1);
}

void	find_path(t_pipex *pipex, char **commands, const char *envp[])
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			pipex->path = (char *)&envp[i][5];
		i++;
	}
	if (!pipex->path)
		print_error(ERR_W);
	split_path(pipex, commands, envp);
}

void	split_path(t_pipex *pipex, char **commands, const char *envp[])
{
	int		i;
	char	*temp_path;

	pipex->paths = ft_split(pipex->path, ':');
	if (!pipex->paths)
		print_error(ERR_W);
	i = 0;
	while (pipex->paths[i] != NULL)
	{
		temp_path = ft_strjoin(pipex->paths[i], "/");
		pipex->path = ft_strjoin(temp_path, commands[0]);
		free(temp_path);
		if (access(pipex->path, F_OK) == 0)
			if (execve(pipex->path, commands, (char *const *)envp) == -1)
				print_error(ERR_W);
		free(pipex->path);
		i++;
	}
	cleanup_pipex(pipex, commands);
	exit(127);
}

/*
void	find_path(t_pipex *pipex, char **commands, const char *envp[])
{
	int		i;
	char	*temp_path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			pipex->path = (char *)&envp[i][5];
		i++;
	}
	pipex->paths = ft_split(pipex->path, ':');
	i = 0;
	while (pipex->paths[i] != NULL)
	{
		temp_path = ft_strjoin(pipex->paths[i], "/");
		pipex->path = ft_strjoin(temp_path, commands[0]);
		free(temp_path);
		if (access(pipex->path, F_OK) == 0)
			if (execve(pipex->path, commands, (char *const *)envp) == -1)
				print_error(ERR_C);
		i++;
	}
	cleanup_pipex(pipex, commands);
	print_error(ERR_C);
}*/
