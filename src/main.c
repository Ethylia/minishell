/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/31 10:01:33 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/readline.h>
#include "readline_extra.h"
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
	int				stat;
	const t_token	*n = findnext(tokens, tfirst);

	if (n->type & (tor | tand | tpipe))
	{
		write(STDERR_FILENO, "minishell: syntax error\n", 24);
		return (258);
	}
	if (!buildcmd(tokens, &(getdata()->cmd)))
	{
		freecmd(&getdata()->cmd);
		return (-1);
	}
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
		while (next->type && (next->type == tand || next->nestlvl > nestlvl))
			next = findnext(next + 1, tand | tor);
	else if (stat == 0)
		while (next->type && (next->type == tor || next->nestlvl > nestlvl))
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
		if (stat == -1)
			return (1);
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
	update_shlvl();
	rl_outstream = stderr;
	updateps1(path);
	data->isinteractive = isatty(STDOUT_FILENO);
	update_env(&data->local_env, "?=0");
	free(path);
	rl_attempted_completion_function = &completion;
	return (data);
}

int	main(int argc, __attribute__((unused))char **argv, char **envp)
{
	char	*line;
	t_token	*atom;

	if (argc > 1)
		return (EXIT_FAILURE);
	init_data((const char **) envp);
	init_sig_handlers();
	line = displayprompt();
	while (line)
	{
		getdata()->tokens = tokenize(line + countwhite(line));
		if (getdata()->tokens)
		{
			add_history(line);
			if (!token_error(getdata()->tokens))
				execline(getdata()->tokens);
			atom = getdata()->tokens;
			getdata()->tokens = 0;
			free(atom);
		}
		free(line);
		line = displayprompt();
	}
	freedata();
	return (atouc(get_var(getdata()->local_env, "?")));
}
