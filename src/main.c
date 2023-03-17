/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/17 10:47:18 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "env.h"
#include "parser/token.h"
#include "util/util.h"
#include "parser/cmd.h"

void	execline(t_token *token)
{
	t_cmd	cmd;
	t_token	*next;
	size_t	plevel;
	int		r;

	next = token;
	plevel = 0;
	while (next->type)
	{
		cmd = buildcmd(next);
		r = execcmd(cmd);
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

	line = readline("msh$ ");
	while (line)
	{
		skipwhite((const char **)&line);
		token = tokenize(line);
		if (token)
		{
			add_history(line);
			execline(token);
			free(token);
		}
		free(line);
		line = readline("msh$ ");
	}
	clear_history();
}
