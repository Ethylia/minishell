/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:44:21 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/22 16:01:13 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "token.h"
#include "cmd.h"

static size_t	tokenlen(t_token *token, enum e_tokens delims)
{
	size_t	i;
	int		q;

	i = 0;
	q = 0;
	if (token->type == tws)
		++i;
	while (token[i].type && (!(token[i].type & delims) || q))
	{
		if (token[i].type & tdqts && q != 2)
			q = (!q);
		if (token[i].type & tqts && q != 1)
			q = (!q) * 2;
		++i;
	}
	if (token[i].type == tws)
		++i;
	return (i);
}

int	toke(t_token *tokens, size_t *i, size_t *j)
{
	*j = tokenlen(tokens + *i
			+ !!(tokens[*i].type & (tdin | tdout | tapp | thdoc)), tdelim);
	if (!*j)
	{
		++i[0];
		return (1);
	}
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
