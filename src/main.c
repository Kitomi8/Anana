/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:32:44 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/16 13:53:38 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**args;
	t_env	*env_list;
	t_token	*tokens;

	t_token *temp;
	(void)ac;
	(void)av;
	(void)envp;
	init_signals();
	env_list = get_env_list(envp);
	while (1)
	{
		g_signal = 0;
		tokens = NULL;
		line = readline("~~minishell: ");
		if (line == NULL)
		{
			printf("miala\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			tokens = ft_lexer(line);
			ft_expand(tokens, env_list);
			if (tokens && tokens->content)
			{
				printf("------------apres expand--------------\n");
				temp = tokens;
				while (temp)
				{
					printf("token: [%s]\n", temp->content);
					temp = temp->next;
				}
				printf("------------------------------------------------\n");
			}
		}
		if (tokens != NULL)
		{
			printf("\n-------------execution du command---------------\n");
			args = token_to_tab(tokens);
			if (args && args[0])
			{
				if (ft_strcmp(args[0], "env") == 0)
					ft_env(env_list);
				else if (ft_strcmp(args[0], "export") == 0)
					ft_export(&env_list, args);
				else if (ft_strcmp(args[0], "unset") == 0)
					ft_unset(&env_list, args);
				else if (ft_strcmp(args[0], "cd") == 0)
					ft_cd(args, &env_list);
				else if (ft_strcmp(args[0], "pwd") == 0)
					ft_pwd();
				else if (ft_strcmp(args[0], "echo") == 0)
					ft_echo(args);
				else
					execute_simple_cmd(args, envp);
				printf("------------------------------------------------\n");
			}
			free_tab(args);
		}
		free(line);
		free_tokens(tokens);
	}
	rl_clear_history();
	return (0);
}
