/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glue.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:32:17 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/03 15:32:52 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*is_glue(char *line)
{
	int		ite;
	int		glue;
	char	*tmp;
	int	is_did;

	is_did = FAIL;
	glue = 0;
	ite = 0;
	while (line[ite])
	{
		while (ft_is_sep_parse(line[ite]) == SUCCESS)
			ite++;
		while (line[ite] && ft_is_sep_parse(line[ite]) == FAIL)
		{
			is_did = FAIL;
			count_quote_arg(line, &ite);
			if (line[ite] == '|' && ft_is_sep_parse(line[ite - 1]) == FAIL)
			{
				printf(RED"letter left"RESET"\n");
				glue = ite;
				is_did = SUCCESS;
			}
			else if (line[ite] == '|' && ft_is_sep_parse(line[ite + 1]) == FAIL)
			{
				printf(RED"letter right"RESET"\n");
				glue = ite + 1;
				is_did = SUCCESS;
			}
			if (is_did == SUCCESS)
			{
				tmp = ft_strdup_len(line, 0, glue);
				tmp = ft_strjoin_lfree(tmp, " ");
				tmp = ft_strjoin_dfree(tmp, ft_strdup_len(line, ft_strlen(tmp) - 1, ft_strlen(line)));
				printf(BACK_GREEN"%s"RST"\n", tmp);
				line = tmp;
				ite = 0;
			}
			ite++;
		}
	}
	(void)tmp;
	(void)glue;
	return (line);
}
