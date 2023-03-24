/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:44:21 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/24 12:56:11 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "token.h"
#include "cmd.h"
#include "util/util.h"
#include "wildcard.h"

static size_t	tokenlen(t_token *token, enum e_tokens delims)
{
	size_t	i;

	i = 0;
	if (token->type == tws)
		++i;
	while (token[i].type && (!(token[i].type & delims) || token[i].quote))
		++i;
	if (token[i].type == tws)
		++i;
	return (i);
}

int	toke(t_token *tokens, size_t *i, size_t *j)
{
	*j = tokenlen(tokens + *i
			+ !!(tokens[*i].type & (tdin | tdout | tapp | thdoc)), tdelim);
	if (!*j)
		return (1);
	return (0);
}

void	setredir(t_cmdgroup *g, enum e_tokens type, t_token *tokens, size_t i)
{
	if (type & (tdin | thdoc))
	{
		g->cmd.redirin[g->c[1].redirin].type = type;
		g->cmd.redirin[g->c[1].redirin].str = concattokens(tokens + 1, i);
		++(g->c[1].redirin);
	}
	else
	{
		g->cmd.redirout[g->c[1].redirout].type = type;
		g->cmd.redirout[g->c[1].redirout].str = concattokens(tokens + 1, i);
		++(g->c[1].redirout);
	}
}

void	buildpipe(t_cmd *cmd, t_token *tokens)
{
	if (findnext(tokens, tpipe)->type)
	{
		cmd->pipecmd = malloc(sizeof(t_cmd));
		*(cmd->pipecmd) = buildcmd(findnext(tokens, tpipe) + 1);
	}
	else
		cmd->pipecmd = 0;
}

void	buildarg(t_cmdgroup *g, t_token *tokens, size_t i)
{
	char	*arg;
	char	**wilds;
	size_t	j;

	arg = concattokens(tokens, i);
	if (strchar(arg, '*'))
	{
		wilds = wildcard_values(arg);
		if (wilds && wilds[0])
		{
			free(arg);
			j = -1;
			g->c[0].argc += wildlen((const char *const *)wilds) - 1;
			g->cmd.argv = ralloc(g->cmd.argv, 8 * (g->c[0].argc + 1),
					wildlen((const char *const *)g->cmd.argv) * sizeof(char *));
			while (wilds[++j])
				g->cmd.argv[g->c[1].argc++] = wilds[j];
			free(wilds);
			return ;
		}
		free_wildcard_values(wilds);
	}
	g->cmd.argv[g->c[1].argc++] = arg;
	return ;
}
