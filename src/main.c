/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/23 13:48:49 by francoma         ###   ########.fr       */
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
#include "error.h"

int	exec_cmd(t_token *tokens)
{
	int		stat;

	getdata()->cmd = buildcmd(tokens);
	if (is_builtin(&getdata()->cmd) && !(getdata()->cmd.pipecmd))
		stat = exec_redir_builtin(&getdata()->cmd);
	else
	{
		stat = pipeline(&getdata()->cmd, 0);
		while (waitpid(ANY_CHILD, 0, 0) != NO_CHILD_LEFT)
			continue ;
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

int	execline(t_token *token)
{
	t_token	*next;
	int		stat;
	// t_cmd	cmd;

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
	return (stat);
}

void	updateps1(const char *path);

static t_data	*init_data(const char **envp)
{
	t_data *const	data = getdata();
	char			*path;

	data->exported_env = copy_env(envp);
	if (!data->exported_env)
		return (NULL);
	if (!get_var(data->exported_env, "PS1"))
		data->local_env = copy_env((const char *[]){"PS1="MSHELLPS, NULL});
	if (!data->local_env)
		return (NULL);
	path = getcwd(NULL, 0);
	if (!path)
		return (NULL);
	updateps1(path);
	free(path);
	return (data);
}

int	main(__attribute__((unused))int argc,
	__attribute__((unused))char **argv, char **envp)
{
	char				*line;
	t_token				*token;

	if (!init_data((const char **) envp))
		exit_error("");
	init_sig_handlers();
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
