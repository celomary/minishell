/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settaqi <settaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 03:19:20 by settaqi           #+#    #+#             */
/*   Updated: 2020/10/14 10:53:27 by settaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_read_or_save(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (((t_files*)tmp->content)->mode == 0 && tmp->next == NULL)
			dup2(((t_files*)tmp->content)->fd, 0);
		else if ((((t_files*)tmp->content)->mode == 1 ||
				((t_files*)tmp->content)->mode == 2) &&
				tmp->next == NULL)
			dup2(((t_files*)tmp->content)->fd, 1);
		else
			close(((t_files*)tmp->content)->fd);
		tmp = tmp->next;
	}
}

void		execute_cmd(t_command *cmd)
{
	if (cmd->builtins >= 1)
		ft_runrightcmd(cmd, 1);
	else
	{
		if (execve(cmd->command[0],
		cmd->command, g_data.envp) == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(cmd->command[0]
				, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
}

void		close_fd(fd, pipe_fd_1, pipe_fd_2)
{
	close(fd);
	close(pipe_fd_1);
	close(pipe_fd_2);
}

void		new_proccess(t_list *tmp_args, int pipefd[], int fd)
{
	dup2(fd, 0);
	if (tmp_args->next != NULL)
		dup2(pipefd[1], 1);
	ft_read_or_save(((t_command*)tmp_args->content)->files);
	execute_cmd(((t_command*)tmp_args->content));
	close_fd(fd, pipefd[0], pipefd[1]);
	exit(0);
}

void		ft_print_multipiperesult(void)
{
	t_list	*tmp_args;
	pid_t	pid;
	int		pipefd[2];
	char	*data;
	int		fd;

	tmp_args = g_data.list_args;
	fd = 0;
	while (tmp_args)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
			new_proccess(tmp_args, pipefd, fd);
		else if (pid < -1)
			ft_putstr_fd("Minishell: can't create a new process\n", 2);
		if (((t_command*)tmp_args->content)->builtins == 3)
			ft_runrightcmd(((t_command*)tmp_args->content), 0);
		wait(NULL);
		close(pipefd[1]);
		fd = dup(pipefd[0]);
		close(pipefd[0]);
		tmp_args = tmp_args->next;
	}
}
