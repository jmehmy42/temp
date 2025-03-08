/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:48:50 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/08 09:21:47 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_files(t_pipex *pipex, char *argv[])
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		perror("Problems with file");
		pipex->infile = open("/dev/null", O_RDONLY);
		if (pipex->infile < 0)
			print_error(ERR_W);
	}
	pipex->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		close(pipex->infile);
		print_error(ERR_FILE);
	}
}

void	ft_pipex(t_pipex *pipex, int *fd, char *argv[], const char *envp[])
{
	handle_files(pipex, argv);
	if (pipe(fd) == -1)
		print_error(ERR_W);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		print_error(ERR_W);
	else if (pipex->pid1 == 0)
	{
		close(fd[0]);
		input_processor(pipex, argv[2], envp, fd);
		exit(0);
	}
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		print_error(ERR_W);
	else if (pipex->pid2 == 0)
	{
		close(fd[1]);
		output_processor(pipex, argv[3], envp, fd);
		exit(0);
	}
	close_and_wait(pipex, fd);
}

void	input_processor(t_pipex *pipex, char *comm_input, const char *envp[],
		int *fd)
{
	char	**commands;

	if (dup2(fd[1], STDOUT_FILENO) < 0)
		print_error(ERR_FILE);
	if (dup2(pipex->infile, STDIN_FILENO) < 0)
		print_error(ERR_FILE);
	close(fd[0]);
	close(pipex->infile);
	close(fd[1]);
	commands = ft_split(comm_input, ' ');
	if (!commands || !commands[0])
	{
		free_string(commands);
		print_error(ERR_C);
	}
	find_path(pipex, commands, envp);
	free_string(commands);
}

void	output_processor(t_pipex *pipex, char *comm_input, const char *envp[],
		int *fd)
{
	char	**commands;

	if (dup2(fd[0], STDIN_FILENO) < 0)
		print_error(ERR_FILE);
	if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
		print_error(ERR_FILE);
	close(fd[1]);
	close(pipex->outfile);
	close(fd[0]);
	commands = ft_split(comm_input, ' ');
	if (!commands || !commands[0])
	{
		free_string(commands);
		print_error(ERR_C);
	}
	find_path(pipex, commands, envp);
	free_string(commands);
}

int	main(int argc, char *argv[], const char *envp[])
{
	int		fd[2];
	t_pipex	pipex;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			print_error(ERR_W);
		ft_pipex(&pipex, fd, argv, envp);
	}
	else
		perror("Wrong amount of arg");
	return (0);
}
