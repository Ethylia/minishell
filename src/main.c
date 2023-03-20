/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/20 16:37:09 by eboyce-n         ###   ########.fr       */
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
		printf("cmd: %s\n", cmd.argv[0]);
		r = pipeline(&cmd, 0);
		freecmd(&cmd);
		waitpid(-1, 0, 0);
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
