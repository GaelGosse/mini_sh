


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:43:09 by gael              #+#    #+#             */
/*   Updated: 2023/03/23 18:27:52 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	init_env_2(char **envp, t_mini_sh *mini_sh)
{
	int	env_length;

	env_length = 0;
	while (envp[env_length])
		env_length++;
	mini_sh->env = (char **)malloc((sizeof (char *)) * (env_length + 1));
	env_length = -1;
	while (envp[++env_length])
		mini_sh->env[env_length] = ft_strdup(envp[env_length]);
	mini_sh->env[env_length] = 0;
}

void	init_prpt(t_mini_sh *mini_sh)
{
	mini_sh->output = readline("minishell>");
	mini_sh->sep = 0;
	mini_sh->sep_2 = 0;
	mini_sh->sep_type = NULL;
	mini_sh->prepare_exec = NULL;
	mini_sh->prepare_exec_type = NULL;
	(void)mini_sh;	
}

int	main(int argc, char *argv[], char **envp)
{
	t_mini_sh	mini_sh;

	if (argc != 1)
		return (printf("minishell won't take any arguments"), 2);
	mini_sh.output = NULL;
	init_env_2(envp, &mini_sh);
	while (1)
	{
		init_prpt(&mini_sh);
		if (!mini_sh.output)
		{
			printf("@exit\n");
			free_all(&mini_sh);
			break ;
		}
		if (mini_sh.output[0])
			add_history(mini_sh.output);
		exec_signal(1);
		if (ft_parsing(&mini_sh) == SUCCESS)
		{
			init_sep_type(&mini_sh);
			init_exec(&mini_sh);
			init_tab_fd(&mini_sh);
			start_exec(&mini_sh);
		}
		free_each_prpt(&mini_sh);
	}
	free_all(&mini_sh);
	(void)argv;
	return (0);
}
