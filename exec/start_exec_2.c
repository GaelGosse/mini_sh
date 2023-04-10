/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:33:14 by mael              #+#    #+#             */
/*   Updated: 2023/04/10 10:36:43 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	init_sep_type(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int		i;

	tmp = mini_sh->rl_out_head;
	if (mini_sh->sep_type)
	{
		free(mini_sh->sep_type);
		mini_sh->sep_type = NULL;
	}
	mini_sh->sep_type = (int*)malloc(sizeof(int) * (mini_sh->sep_2 + 1));
	if (!mini_sh->sep_type)
		return (FAIL_MALLOC);
	i = 0;
	while (tmp)
	{
		if (is_sep(tmp->word) == SUCCESS)
		{
			mini_sh->sep_type[i] = tmp->type;
			i++;
		}
		tmp = tmp->next;
	}
	mini_sh->sep_type[i] = 0;
	mini_sh->sep_id = 0;
	return (SUCCESS);
}

void	exec_cmd(t_mini_sh *mini_sh, int i_exec)
{
	char	*cmd_abs_path;

	cmd_abs_path = NULL;
	if (access(mini_sh->prepare_exec[i_exec][0], X_OK) == 0)
		execve(mini_sh->prepare_exec[i_exec][0], mini_sh->prepare_exec[i_exec], mini_sh->env);
	cmd_abs_path = ft_find_path_2(mini_sh, mini_sh->prepare_exec[i_exec][0]);
	if (cmd_abs_path != NULL)
	{
		free(mini_sh->prepare_exec[i_exec][0]);
		mini_sh->prepare_exec[i_exec][0] = cmd_abs_path;
		execve(cmd_abs_path, mini_sh->prepare_exec[i_exec], mini_sh->env);
	}
	else
	{
		if (mini_sh->len_prepare_exec > 1 && mini_sh->sep_type[i_exec - 1] != PIPE)
			return ;
		else
		{
			printf("minishell:%s: command not found\n", \
			mini_sh->prepare_exec[i_exec][0]);
			free_all(mini_sh);
			exit (127);
		}
	}
}

// int	init_tab_fd(t_mini_sh *mini_sh)
// {
// 	int	i_init_fd;

// 	i_init_fd = 0;
// 	if (mini_sh->sep_2 == 0)
// 		return (opening_redir_r_file(mini_sh));
// 	mini_sh->exec->tab_fd = malloc(sizeof(int *) * (mini_sh->sep_2 + 1));
// 	if (!mini_sh->exec->tab_fd)
// 		return (FAIL_MALLOC);
// 	mini_sh->exec->tab_fd[mini_sh->sep_2] = 0;
// 	while (i_init_fd < mini_sh->sep_2)
// 	{
// 		mini_sh->exec->tab_fd[i_init_fd] = malloc(sizeof(int) * 3);
// 		mini_sh->exec->tab_fd[i_init_fd][2] = 0;
// 		if (pipe(mini_sh->exec->tab_fd[i_init_fd]) == -1)
// 			return (printf(BACK_RED"pipe not working"RST"\n"), FAIL);
// 		//if_redir(mini_sh, i_init_fd);
// 		// opening_redir_r_file(mini_sh, i_init_fd);
// 		i_init_fd++;
// 	}
// 	// opening_redir_r_file(mini_sh);
// 	return (SUCCESS);
// 	(void)i_init_fd;
// }

int	init_tab_fd(t_mini_sh *mini_sh)
{
	int		i_init_fd;
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	i_init_fd = -1;
	if (mini_sh->sep_2 == 0)
		return (opening_redir_r_file(mini_sh, tmp, i_init_fd));
	free_tab_fd(mini_sh);
	mini_sh->exec->tab_fd = NULL;
	mini_sh->exec->tab_fd = malloc(sizeof(int *) * (mini_sh->sep_2 + 1));
	if (!mini_sh->exec->tab_fd)
		return (FAIL_MALLOC);
	while (tmp && ++i_init_fd < mini_sh->sep_2)
	{
		if (!tmp)
			break ;
		while (tmp && is_sep_int(tmp->type) == FAIL)
			tmp = tmp->next;
		if (!tmp)
			break ;
		mini_sh->exec->tab_fd[i_init_fd] = malloc(sizeof(int) * 3);
		mini_sh->exec->tab_fd[i_init_fd][2] = 0;
		if (pipe(mini_sh->exec->tab_fd[i_init_fd]) == -1)
			return (printf(BACK_RED"pipe not working"RST"\n"), FAIL);
		if (tmp && tmp->type == PIPE && is_sep_int(tmp->next->type) == SUCCESS)
		{
			close(mini_sh->exec->tab_fd[i_init_fd][0]);
			mini_sh->exec->tab_fd[i_init_fd][0] = 0;
			tmp = tmp->next;
		}
		if (tmp)
			opening_redir_r_file(mini_sh, tmp, i_init_fd);
		tmp = tmp->next;
	}
	mini_sh->exec->tab_fd[i_init_fd] = NULL;
	return (SUCCESS);
}

int	exec_builtin(t_mini_sh *mini_sh, int i)
{
	if (mini_sh->len_prepare_exec == 1)
	{
		if (do_built_in(mini_sh, i) == FAIL)
			return (FAIL);
		else
			return (SUCCESS);
	}
	return (FAIL);
}

int	exec_redir(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_type[i_exec] == REDIR_R)
		do_redir_r(mini_sh, i_exec);
	if (mini_sh->sep_type[i_exec] == APPEND)
		do_append(mini_sh, i_exec);
	(void)i_exec;
	(void)mini_sh;
	return (SUCCESS);
}

int	init_fd_exec(t_mini_sh *mini_sh, int i_exec)
{
	if (i_exec == 0)
		mini_sh->exec->fd_in = 0;
	else
		mini_sh->exec->fd_in = mini_sh->exec->tab_fd[i_exec - 1][0];
	if (i_exec + 1 == mini_sh->len_prepare_exec)
		mini_sh->exec->fd_out = 1;
	else
		mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i_exec][1];
	if (exec_redir(mini_sh, i_exec) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

void	close_all(t_mini_sh *mini_sh)
{
	int	i_close_pipe;

	i_close_pipe = 0;
	while (i_close_pipe < mini_sh->sep_2)
	{
		if (mini_sh->exec->tab_fd[i_close_pipe][0] > 2)
			close(mini_sh->exec->tab_fd[i_close_pipe][0]);
		if (mini_sh->exec->tab_fd[i_close_pipe][1] > 2)
			close(mini_sh->exec->tab_fd[i_close_pipe][1]);
		i_close_pipe++;
	}
}


void	child_process(t_mini_sh *mini_sh, int i_exec)
{
	if (init_fd_exec(mini_sh, i_exec) == FAIL)
		exit (1);
	fprintf(stderr, BOLD_PURPLE"cmd: "BACK_PURPLE"%s"RST"\n", mini_sh->prepare_exec[i_exec][0]);
	fprintf(stderr, PURPLE"fd_in: %i"RST"\n", mini_sh->exec->fd_in);
	fprintf(stderr, PURPLE"fd_out: %i"RST"\n\n", mini_sh->exec->fd_out);
	dup2(mini_sh->exec->fd_in, 0);
	dup2(mini_sh->exec->fd_out, 1);
	close_all(mini_sh);
	if (exec_builtin(mini_sh, i_exec) == FAIL)
		exec_cmd(mini_sh, i_exec);
	free_all(mini_sh);
	exit (1);
}

int	start_exec(t_mini_sh *mini_sh)
{
	int i_exec;

	i_exec = 0;
	mini_sh->pids = (pid_t *)malloc((sizeof (pid_t)) * (mini_sh->sep_2 + 1));
	if (!mini_sh->pids)
		return (FAIL_MALLOC);
	while (mini_sh->prepare_exec[i_exec])
	{
		if (exec_builtin(mini_sh, i_exec) == FAIL)
		{
			mini_sh->pids[i_exec] = fork();
			if (mini_sh->pids[i_exec] == -1)
				return (FAIL);
			if (mini_sh->pids[i_exec] == 0)
				child_process(mini_sh, i_exec);
		}
		else
			mini_sh->pids[i_exec] = FAIL;
		i_exec++;
	}
	close_all(mini_sh);
	i_exec = 0;
	while (mini_sh->prepare_exec[i_exec])
	{
		if (mini_sh->pids[i_exec] != FAIL)
			waitpid(mini_sh->pids[i_exec], NULL, 0);
		i_exec++;
	}
	return (SUCCESS);
}
