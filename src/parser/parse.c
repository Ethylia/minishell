/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:29:19 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/23 09:24:49 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

#include "util/util.h"

static void	skiparg(t_token **tokens)
{
	if ((*tokens)->type & (tdin | tdout | thdoc | tapp))
		++(*tokens);
	if ((*tokens)->type & (tws))
		++(*tokens);
	while (1)
	{
		if (!(*tokens)->type || ((*tokens)->type
				& (tdelim) && (!(*tokens)->quote)))
			break ;
		++(*tokens);
	}
	if ((*tokens)->type & (tws))
		++(*tokens);
}

static t_counts	countargs(t_token *tokens)
{
	t_counts	c;

	c.argc = 0;
	c.redirin = 0;
	c.redirout = 0;
	while (tokens->type)
	{
		if (tokens->type & (tpipe | tand | tor))
			break ;
		if (tokens->type & (tdin | thdoc))
			skiparg(&tokens + (++c.redirin) * 0);
		else if (tokens->type & (tdout | tapp))
			skiparg(&tokens + (++c.redirout) * 0);
		else if (tokens->type & (td | twrd))
			skiparg(&tokens + (++c.argc) * 0);
		else
			++tokens;
	}
	return (c);
}

static int	initcmd(t_cmdgroup *g, t_token *tokens)
{
	g->cmd.argv = malloc(sizeof(char *) * (g->c[0].argc + 1));
	g->cmd.redirin = malloc(sizeof(t_redir) * (g->c[0].redirin + 1));
	g->cmd.redirout = malloc(sizeof(t_redir) * (g->c[0].redirout + 1));
	if (!g->cmd.argv || !g->cmd.redirin || !g->cmd.redirout)
	{
		free(g->cmd.argv);
		free(g->cmd.redirin);
		free(g->cmd.redirout);
		return (0);
	}
	g->cmd.argv[g->c[0].argc] = 0;
	g->cmd.redirin[g->c[0].redirin].str = 0;
	g->cmd.redirin[g->c[0].redirin].type = 0;
	g->cmd.redirout[g->c[0].redirout].str = 0;
	g->cmd.redirout[g->c[0].redirout].type = 0;
	g->cmd.pipecmd = 0;
	g->c[1].argc = 0;
	g->c[1].redirin = 0;
	g->c[1].redirout = 0;
	g->i[0] = 0;
	buildpipe(&g->cmd, tokens);
	return (1);
}

t_cmd	buildcmd(t_token *tokens)
{
	t_cmdgroup		g;

	g.c[0] = countargs(tokens);
	initcmd(&g, tokens);
	while (g.c[0].argc != g.c[1].argc || g.c[0].redirin != g.c[1].redirin
		|| g.c[0].redirout != g.c[1].redirout)
	{
		if (tokens[g.i[0]].type & (tdin | tdout | tapp | thdoc | td | twrd))
		{
			if (toke(tokens, &g.i[0], &g.i[1]))
				continue ;
			if (tokens[g.i[0]].type & (tdin | thdoc | tdout | tapp))
				setredir(&g,
					tokens[g.i[0]].type, tokens + g.i[0] + 1, g.i[1]);
			else if (tokens[g.i[0]].type & (td | twrd))
				buildarg(&g, tokens + g.i[0], g.i[1]);
			g.i[0] += g.i[1];
		}
		else
			++g.i[0];
	}
	g.cmd.argv[g.c[1].argc] = 0;
	return (g.cmd);
}

void	freecmd(t_cmd *cmd)
{
	size_t	i;

	if (cmd->pipecmd)
		freecmd(cmd->pipecmd);
	cmd->pipecmd = 0;
	i = -1;
	while (cmd->argv && cmd->argv[++i])
		free(cmd->argv[i]);
	free(cmd->argv);
	i = -1;
	while (cmd->redirin && cmd->redirin[++i].type)
		free(cmd->redirin[i].str);
	free(cmd->redirin);
	i = -1;
	while (cmd->redirout && cmd->redirout[++i].type)
		free(cmd->redirout[i].str);
	free(cmd->redirout);
	cmd->argv = 0;
	cmd->redirin = 0;
	cmd->redirout = 0;
}
