/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:54:13 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/07 22:06:11 by jmehmy           ###   ########.fr       */
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
    int status;
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

void    handle_files(t_pipex *pipex, char *argv[])
{
    pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		perror("Problems with file");
		pipex->infile = open("/dev/null", O_RDONLY);
		if (pipex->infile < 0)	
		{
			perror("Failed to open /dev/null");
			exit(1);
		}
	}
		pipex->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (pipex->outfile < 0)
	{
		close(pipex->infile);
		perror("Problems with file");
		exit(1);
	}
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
void	find_path(t_pipex *pipex, char **commands, const char *envp[])
{
    int		i;
    char	*temp_path;

    i = -1;
    while (envp[++i] != NULL)
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            if (!(pipex->paths = ft_split(&envp[i][5], ':')))
                print_error("Error splitting PATH");
            break;
        }
    if (!pipex->paths)
        print_error("Error splitting PATH");
    i = -1;
    while (pipex->paths[++i] != NULL)
    {
        temp_path = ft_strjoin(pipex->paths[i], "/");
        pipex->path = ft_strjoin(temp_path, commands[0]);
        free(temp_path);
        if (access(pipex->path, F_OK) == 0)
           if(execve(pipex->path, commands, (char *const *)envp) == -1)
				perror("execve failed"), exit(1);
		free(pipex->path);
    }
    cleanup_pipex(pipex, commands), exit(127);
}

