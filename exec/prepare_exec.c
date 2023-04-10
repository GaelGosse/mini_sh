/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:52:27 by gael              #+#    #+#             */
/*   Updated: 2023/04/10 15:09:35 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	count_word_for_alloc(t_mini_sh *mini_sh, t_parse *rlout)
{
	t_parse	*tmp;

	tmp = rlout;
	mini_sh->nbr_word = 0;
	if (!tmp)
		return (FAIL);
	if (is_sep(tmp->word) == SUCCESS)
		tmp = tmp->next;
	while (tmp)
	{
		if (is_sep(tmp->word) == SUCCESS)
			return (SUCCESS);
		mini_sh->nbr_word++;
		if (tmp)
			tmp = tmp->next;
	}
	return (SUCCESS);
}

int	prepare_exec(t_mini_sh *mini_sh)
{
	int	triple;

	if (init_big_tab(mini_sh) == FAIL)
		return (FAIL);
	triple = 0;
	while (mini_sh->rl_out)
	{
		if (count_word_for_alloc(mini_sh, mini_sh->rl_out) == FAIL)
			return (FAIL);
		mini_sh->prepare_exec[triple] = (char **)malloc((sizeof (char *)) * \
		(mini_sh->nbr_word + 1));
		mini_sh->prepare_exec_type[triple] = malloc((sizeof (int )) * \
		(mini_sh->nbr_word + 1));
		fill_little_tab(mini_sh, triple);
		triple++;
		if (!mini_sh->rl_out->next)
			break ; 
		else
		{
			while (is_sep(mini_sh->rl_out->word) == SUCCESS)
				mini_sh->rl_out = mini_sh->rl_out->next;
		}
	}
	end_prepare_exec(mini_sh, triple);
	print_prep_exec(mini_sh);
	return (SUCCESS);
}

void	print_prep_exec(t_mini_sh *mini_sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("START_PRINT\n");
	while (mini_sh->prepare_exec[i])
	{
		j = 0;
		while (mini_sh->prepare_exec[i][j])
		{
			printf(BACK_CYAN"%s"RST"\n", mini_sh->prepare_exec[i][j]);
			print_type(mini_sh->prepare_exec_type[i][j]);
			printf("\n");
			j++;
		}
		i++;
		printf(GREEN"----"RST"\n\n");
	}
	printf("END_PRINT\n");
}

void	end_prepare_exec(t_mini_sh *mini_sh, int triple)
{
	mini_sh->prepare_exec[triple] = NULL;
	mini_sh->prepare_exec_type[triple] = NULL;
	mini_sh->len_prepare_exec = triple;
}
