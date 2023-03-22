/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/22 08:20:22 by eboyce-n         ###   ########.fr       */
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
#include "data.h"

int	exec_cmd(t_token *tokens)
{
	int		stat;

	getdata()->cmd = buildcmd(tokens);
	if (is_builtin(&getdata()->cmd) && !(getdata()->cmd.pipecmd))
		stat = exec_builtin(&getdata()->cmd);
	else
	{
		stat = pipeline(&getdata()->cmd, 0);
		if (stat == ERROR)
			stat = EXIT_FAILURE;
		waitpid(ANY_CHILD, 0, 0);
	}
	freecmd(&getdata()->cmd);
	// printf("$?: %i\n", stat);
	return (stat);
}

t_token	*nextcmd(t_token *token, int stat)
{
	t_token			*next;
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

	getdata()->exported_env = copy_env((const char **)envp);
	init_sig_handlers();
	if (!get_var(getdata()->exported_env, "PS1"))
		(getdata())->local_env
			= copy_env((const char *[]){"PS1="MSHELLPS, NULL});
	line = readline(get_var(getdata()->local_env, "PS1"));
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
		line = readline(get_var(getdata()->local_env, "PS1"));
	}
	rl_clear_history();
	freedata();
}
