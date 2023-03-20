/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/20 13:52:09 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "readline_extra.h"
#include "parser/token.h"
#include "parser/cmd.h"
#include "util/util.h"
#include "env.h"
#include "def.h"
#include "sig.h"

void	execline(t_token *token)
{
	t_cmd	cmd;
	t_token	*next;
	int		r;

	next = token;
	while (next->type)
	{
		cmd = buildcmd(next);
		r = 0;
		for(int i = 0; cmd.argv[i]; i++)
			printf("%s ", cmd.argv[i]);
		for(int i = 0; cmd.redirin[i]; i++)
			printf("< %s ", cmd.redirin[i]);
		for(int i = 0; cmd.redirout[i]; i++)
			printf("> %s ", cmd.redirout[i]);
		freecmd(&cmd);
		next = findafter(next, tand | tor);
		if (!next->type)
			break ;
		if (r == 0 && next->type == tand)
			next = findafter(next, tand | tor);
		else if (r != 0 && next->type == tor)
			next = findafter(next, tand | tor);
	}
}

int	main(__attribute__((unused))int argc,
	__attribute__((unused))char **argv, __attribute__((unused))char **env)
{
	char				*line;
	t_token				*token;

	init_sig_handlers();
	line = readline(MINISHELL_PS);
	while (line)
	{
		token = tokenize(line + countwhite(line));
		if (token)
		{
			add_history(line);
			execline(token);
			free(token);
		}
		free(line);
		line = readline(MINISHELL_PS);
	}
	rl_clear_history();
}
