/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/21 15:47:28 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "readline_extra.h"
#include "parser/token.h"
#include "pipeline.h"
#include "builtins/builtins.h"
#include "util/util.h"
#include "env.h"
#include "def.h"
#include "sig.h"

#include <stdio.h>
int	exec_cmd(t_token *tokens)
{
	t_cmd	cmd;
	int		stat;

	cmd = buildcmd(tokens);
	if (is_builtin(&cmd) && !cmd.pipecmd)
		stat = exec_builtin(&cmd);
	else
	{
		if (pipeline(&cmd, 0) == ERROR)
			stat = EXIT_FAILURE;
		else
		{
			while (waitpid(ANY_CHILD, &stat, 0) != NO_CHILD_LEFT)
				;
			stat = WEXITSTATUS(stat);
		}
	}
	freecmd(&cmd);
	printf("$?: %i\n", stat);
	return (stat);
}

t_token	*nextcmd(t_token *token, int stat)
{
	t_token	*next;
	unsigned int	nestlvl;

	next = findnext(token, tand | tor);
	nestlvl = next->nestlvl;
	if (!next->type)
		return (next);
	if (stat != 0)
		while (next->type == tand || next->nestlvl > nestlvl)
			next = findnext(next + 1, tand | tor);
	else if (stat == 0)
		while (next->type == tor || next->nestlvl > nestlvl)
			next = findnext(next + 1, tand | tor);
	if (next->type)
		++next;
	return (next);
}

void	execline(t_token *token)
{
	t_token	*next;
	// t_cmd	cmd;
	int		stat;

	next = token;
	while (next->type)
	{
		// cmd = buildcmd(next);
		// printf("cmd: %s\n", cmd.argv[0]);
		// general exec_cmd which
		//		distinguishes single builtin from pipeline
		//		retrieves exit status
		//		freecmd
		stat = exec_cmd(next);
		next = nextcmd(next, stat);
	}
}

int	main(__attribute__((unused))int argc,
	__attribute__((unused))char **argv, char **envp)
{
	char				*line;
	t_token				*token;

	set_exported_env(envp);
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
