/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:47:28 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/10 16:05:50 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	check_redi_r_append_error_1(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == REDIR_R || tmp->type == APPEND)
		{
			tmp = tmp->next;
			if (opendir(tmp->word) != NULL)
			{
				if (print_error(1, tmp) == FAIL)
					return (FAIL);
			}
			if (tmp->type == _FILE || tmp->type == CMD_ABS)
			{
				if (access(tmp->word, W_OK) == -1)
				{
					if (print_error(2, tmp) == FAIL)
						return (FAIL);
				}
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_redi_r_append_error_2(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == REDIR_R || tmp->type == APPEND)
		{
			tmp = tmp->next;
			if ((tmp->type == _FILE \
			&& (access(tmp->word, W_OK) == 0)) || tmp->type == ARG)
			{
				if (tmp->next && (is_sep(tmp->next->word) == FAIL))
				{
					if (print_error(4, tmp) == FAIL)
						return (FAIL);
				}
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_redir_follow(t_mini_sh *mini_sh)
{
	t_parse *tmp;
	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (is_sep_int(tmp->type) == SUCCESS)
		{
			if (tmp->next && is_sep_int(tmp->next->type) == SUCCESS)
				return (print_error(4, tmp), FAIL);
			// else if (tmp->next && tmp->next->next && is_sep_int(tmp->next->next->type) == FAIL)
			// 	return (print_error_2(1, tmp), FAIL);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_redi_r_append_error(t_mini_sh *mini_sh)
{
	if (check_redir_follow(mini_sh) == FAIL)
		return (FAIL);
	else if (check_redi_r_append_error_1(mini_sh) == FAIL)
		return (FAIL);
	else if (check_redi_r_append_error_2(mini_sh) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	print_error(int index, t_parse *tmp)
{
	if (index == 1)
	{
		printf("minishell: %s: Is a directory\n", tmp->word);
		return (FAIL);
	}
	else if (index == 2)
	{
		printf("minishell: %s: permission denied\n", tmp->word);
		return (FAIL);
	}
	else if (index == 3)
	{
		printf("minishell: cannot access '%s' : No such file or directory\n", \
		tmp->word);
		return (FAIL);
	}
	else if (index == 4)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", \
		tmp->word);
		return (FAIL);
	}
	return (SUCCESS);
}

int	print_error_2(int index, t_parse *tmp)
{
	if (index == 1)
	{
		printf("minishell: case not handle\n");
		return (FAIL);
	}
	(void)tmp;
	return (SUCCESS);
}
