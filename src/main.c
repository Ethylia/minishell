/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/24 10:07:11 by eboyce-n         ###   ########.fr       */
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
#include "prompt.h"

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
	return (stat);
}

t_token	*nextcmd(t_token *token, int stat)
{
	t_token			*next;
	unsigned int	nestlvl;

	next = findnext(token, tand | tor);
	if (!next->type)
		return (next);
	nestlvl = next->nestlvl;
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
	char	*res[2];
	int		stat;

	next = token;
	while (next->type)
	{
		stat = exec_cmd(next);
		next = nextcmd(next, stat);
		res[0] = intoa(stat);
		res[1] = concatstr(2, "?=", res[0]);
		free(res[0]);
		update_env(&(getdata()->local_env), res[1]);
		free(res[1]);
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
		exit_error("");
	if (!get_var(data->exported_env, "PS1"))
		data->local_env = copy_env((const char *[]){"PS1="MSHELLPS, NULL});
	if (!data->local_env)
		exit_error("");
	path = getcwd(NULL, 0);
	if (!path)
		exit_error("");
	updateps1(path);
	data->isinteractive = isatty(STDIN_FILENO);
	update_env(&data->local_env, "?=0");
	free(path);
	return (data);
}

int	main(__attribute__((unused))int argc,
	__attribute__((unused))char **argv, char **envp)
{
	char				*line;
	t_token				*token;

	init_data((const char **) envp);
	init_sig_handlers();
	line = displayprompt();
	getdata()->intflag = 0;
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
		line = displayprompt();
		getdata()->intflag = 0;
	}
	freedata();
	return (EXIT_SUCCESS);
}
