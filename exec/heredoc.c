/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:20:26 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/10 14:53:39 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

// int	there_is_a_heredoc(t_mini_sh *mini_sh, int i)
// {
// 	while (mini_sh->sep_type[i])
// 	{
// 		if (ft_strncmp("<<", mini_sh->prepare_exec[i][j], ft_strlen(mini_sh->prepare_exec[i][j])) == 0)
// 		{
// 			if (j == 0)
// 				return (1);
// 			else if (j == 1)
// 				return (2);
// 			else if (j > 1)
// 				return (3);
// 			else if (j > 2)
// 				return (FAIL);
// 		}
// 		j++;
// 	}
// 	return (FAIL);
// }

// int	witch_heredoc(t_mini_sh *mini_sh, int i)
// {
// 	int j;

// 	j = 0;
// 	if (there_is_a_heredoc(mini_sh, i) == FAIL)
// 		return (FAIL);
// 	else if (there_is_a_heredoc(mini_sh, i) == 1)
// 		do_simple_heredoc(mini_sh, i);
// 	// else if (there_is_a_heredoc(mini_sh, i) == 2)
// 	// 	do_heredoc_cmd(mini_sh);
// 	// else if (there_is_a_heredoc(mini_sh, i) == 3)
// 	// 	do_heredoc_big_cmd(mini_sh);
// 	return (SUCCESS);
// }

// int	do_simple_heredoc(t_mini_sh *mini_sh, int i)
// {
// 	char *input;


// 	while (1)
// 	{
// 		input = readline(">");

// 	}
// }

// int	init_heredoc(t_mini_sh *mini_sh)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (mini_sh->sep_type[i])
// 	{
// 		if (mini_sh->sep_type[i] == HR_DOC)
// 			j++;
// 		i++;
// 	}
// 	// printf(RED"j = %d"RST"\n", j);
// 	mini_sh->hr_doc_tab = (int *)malloc(sizeof(int) * j + 1);
// 	if (!mini_sh->hr_doc_tab)
// 		return (FAIL_MALLOC);
// 	mini_sh->hr_doc_tab[j] = 0;
// 	i = 0;
// 	while (j > 0)
// 	{
// 		mini_sh->file_heredoc = ft_strjoin_rfree(".heredoc", ft_itoa(i));
// 		mini_sh->hr_doc_tab[i] = open(mini_sh->file_heredoc, O_CREAT | O_RDWR, 0777);
// 		// printf(BACK_BLUE"hr_doc = %d"RST"\n", mini_sh->hr_doc_tab[i]);
// 		if (!mini_sh->hr_doc_tab[i])
// 			return (FAIL_MALLOC);
// 		i++;
// 		j--;
// 	}
// 	return (SUCCESS);
// }

// int	there_is_a_heredoc(t_mini_sh *mini_sh, int i_exec)
// {
// 	if (init_heredoc(mini_sh) != 1)
// 		return (FAIL);
// 	else
// 	{
// 		//if_hr_doc(mini_sh);
// 		if (i_exec == 0 || mini_sh->sep_type[i_exec - 1] == PIPE)
// 			do_simple_heredoc(mini_sh, i_exec);
// 	}
// 	return (SUCCESS);
// }


// //quand seulement heredoc
// int	do_simple_heredoc(t_mini_sh *mini_sh, int i_exec)
// {
// 	int i_close;
// 	char *input;

// 	//printf("hehe\n");
// 	while (1)
// 	{
// 		dup2(0, 0);
// 		dup2(1, 1);
// 		input = readline("&>");

// 		// close(mini_sh->exec->tab_fd[i_exec][0]);
// 		if (ft_strncmp(input, mini_sh->prepare_exec[i_exec][0], ft_strlen(mini_sh->prepare_exec[i_exec][0])) == 0)
// 		{
// 			i_close = 0;
// 			while (mini_sh->exec->tab_fd[i_close])
// 			{
// 				close(mini_sh->exec->tab_fd[i_close][0]);
// 				close(mini_sh->exec->tab_fd[i_close][1]);
// 				i_close++;
// 			}
// 			exit(1);
// 			break ;
// 			//fprintf(stderr, "break\n");
// 		}
// 		//dup2(mini_sh->hr_doc_tab[i_exec], 1);
// 		//printf("%s\n", input);
// 		ft_putstr_fd(input, mini_sh->hr_doc_tab[0]);
// 	}
// 	unlink(mini_sh->file_heredoc);
// 	free(mini_sh->file_heredoc);
// 	return (SUCCESS);
// }

// int	heredoc_cmd(t_mini_sh *mini_sh)
// {

// }

void	open_hrdoc(t_mini_sh *mini_sh)
{
	char	*filename;
	int		ite_file;

	ite_file = 0;
	// mini_sh->exec->fd_hr = malloc((sizeof (int)) * (2));
	filename = ft_strjoin_rfree(".heredoc", ft_itoa(ite_file));
	while (access(filename, F_OK) == 0)
	{
		// mini_sh->exec->fd_hr = malloc((sizeof (int)) * (2));
		filename = ft_strjoin_rfree(".heredoc", ft_itoa(ite_file));
		ite_file++;
	}
	mini_sh->exec->fd_hr = open(filename, O_CREAT | O_RDWR, 0644);
	printf(GREEN"filename: %s"RESET"\n", filename);
	(void)mini_sh;
}

void	close_hrdoc(t_mini_sh *mini_sh)
{
	char	*filename;
	int		ite_file;

	ite_file = 0;
	// mini_sh->exec->fd_hr = malloc((sizeof (int)) * (2));
	filename = ft_strjoin_rfree(".heredoc", ft_itoa(ite_file));
	while (access(filename, F_OK) == 0)
	{
		// mini_sh->exec->fd_hr = malloc((sizeof (int)) * (2));
		filename = ft_strjoin_rfree(".heredoc", ft_itoa(ite_file));
		ite_file++;
	}
	mini_sh->exec->fd_hr = open(filename, O_CREAT | O_RDWR, 0644);
	printf(GREEN"filename: %s"RESET"\n", filename);
	(void)mini_sh;
}

// int	if_hrdoc(t_mini_sh *mini_sh)
// {
// 	char	*input;
// 	int		i_hrdoc;

// 	i_hrdoc = 0;
// 	input = NULL;
// 	while (mini_sh->prepare_exec[i_hrdoc])
// 	{
// 		if ((mini_sh->sep_type[i_hrdoc] && mini_sh->sep_type[i_hrdoc] == HR_DOC && mini_sh->prepare_exec_type[i_hrdoc][0] == EOFL)
// 		|| (mini_sh->sep_type[i_hrdoc - 1] && mini_sh->sep_type[i_hrdoc - 1] == HR_DOC && mini_sh->prepare_exec_type[i_hrdoc][0] == EOFL))
// 		{
// 			open_hrdoc(mini_sh);
// 			while (1)
// 			{
// 				input = readline("@>");
// 				if (ft_strncmp(input, mini_sh->prepare_exec[i_hrdoc][0], ft_strlen(input)) == 0)
// 				{
// 					close_all(mini_sh);
// 					return(SUCCESS);
// 				}
// 				ft_putstr_fd(input, mini_sh->exec->fd_hr);
// 			}
// 			if (mini_sh->exec->tab_fd[i_hrdoc][1] > 2)
// 				close(mini_sh->exec->tab_fd[i_hrdoc][1]);
// 			mini_sh->exec->fd_out = mini_sh->exec->fd_r;
// 		}
// 	}
// 	return (SUCCESS);
// }
