/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:44:21 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/21 15:25:39 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "token.h"

int	toke(t_token *tokens, size_t *i, size_t *j)
{
	*j = tokenlen(tokens + *i + !!(tokens[*i].type & (tdin | tdout | tapp | thdoc)), tdelim);
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
		g->cmd.redirin[g->c[1].redirin].str = concattokens(tokens, i);
		++(g->c[1].redirin);
	}
	else
	{
		g->cmd.redirout[g->c[1].redirout].type = type;
		g->cmd.redirout[g->c[1].redirout].str = concattokens(tokens, i);
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
