/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:04:44 by gael              #+#    #+#             */
/*   Updated: 2023/04/09 21:44:01 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

t_parse	*ft_lstnew_word(char *content, int save, int ite)
{
	t_parse	*new;

	new = (t_parse *)malloc(sizeof(t_parse));
	if (!new)
		return (NULL);
	new->type = 0;
	new->word = ft_strdup_len(content, save, ite);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
