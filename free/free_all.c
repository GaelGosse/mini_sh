/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:50:16 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/03 11:43:26 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	free_each_prpt(t_mini_sh *mini_sh)
{
	free_parsing(mini_sh);
	free_exec(mini_sh);
}

void	free_all(t_mini_sh *mini_sh)
{
	free_each_prpt(mini_sh);
	free_env(mini_sh);
	free_env_sorted(mini_sh);
	free_data(mini_sh);
}
