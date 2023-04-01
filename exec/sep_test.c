/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:19:30 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/01 19:19:35 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	if_hr_doc(t_mini_sh *mini_sh)
{
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == HR_DOC)
		{
			if (tmp->next && tmp->next->next && tmp->next->next->word)
				mini_sh->sep_2++;
		}
		tmp = tmp->next;
	}
}
