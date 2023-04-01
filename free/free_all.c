/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:50:16 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/01 18:18:47 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	free_each_prpt(t_mini_sh *mini_sh)
{
	free(mini_sh->output);
	mini_sh->output = NULL;
	free_parsing(mini_sh);
	free_type(mini_sh);
	if (mini_sh->prepare_exec)
		free_exec(mini_sh);
	if (mini_sh->prepare_exec_type)
		free_exectype(mini_sh);
}

void	free_all(t_mini_sh *mini_sh)
{
	free_env(mini_sh);
	free(mini_sh->data);
	mini_sh->data = NULL;
	free(mini_sh->exec);
	mini_sh->exec = NULL;
	free(mini_sh->pids);
	mini_sh->pids = NULL;
	free_each_prpt(mini_sh);
}
