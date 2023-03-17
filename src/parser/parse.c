/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:29:19 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/17 15:51:11 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

#include "util/util.h"

static void	skiparg(t_token **tokens)
{
	while ((*tokens)->type & (tws))
		++(*tokens);
	while ((*tokens)->type & (td | twrd))
		++(*tokens);
	while ((*tokens)->type & (tws))
		++(*tokens);
}

typedef struct s_counts
{
	size_t	argc;
	size_t	redirin;
	size_t	redirout;
}	t_counts;

static t_counts	countargs(t_token *tokens)
{
	size_t		i;
	t_counts	c;

	i = -1;
	c.argc = 0;
	c.redirin = 0;
	c.redirout = 0;
	while (tokens[++i].type)
	{
		if (tokens[i].type & (tpipe | tand | tor))
			break ;
		if (tokens[i].type & (tdin))
			skiparg(&tokens + (++c.redirin) * 0);
		else if (tokens[i].type & (tdout))
			skiparg(&tokens + (++c.redirout) * 0);
		else if (tokens[i].type & (td | twrd))
			skiparg(&tokens + (++c.argc) * 0);
	}
	return (c);
}

static int	initcmd(t_cmd *cmd, t_counts c)
{
	cmd->argv = malloc(sizeof(char *) * (c.argc + 1));
	cmd->redirin = malloc(sizeof(char *) * (c.redirin + 1));
	cmd->redirout = malloc(sizeof(char *) * (c.redirout + 1));
	if (!cmd->argv || !cmd->redirin || !cmd->redirout)
	{
		free(cmd->argv);
		free(cmd->redirin);
		free(cmd->redirout);
		return (0);
	}
	cmd->argv[c.argc] = 0;
	cmd->redirin[c.redirin] = 0;
	cmd->redirout[c.redirout] = 0;
	return (1);
}

t_cmd	buildcmd(t_token *tokens)
{
	t_cmd			cmd;
	size_t			i;
	const t_counts	c = countargs(tokens);
	t_counts		c2;

	initcmd(&cmd, c);
	c2.argc = 0;
	c2.redirin = 0;
	c2.redirout = 0;
	i = 0;
	while (c2.argc != c.argc || c2.redirin != c.redirin
		|| c2.redirout != c.redirout)
	{
		if (tokens[i].type & (tdin))
			cmd.redirin[c2.redirin++] = concattokens(tokens + i + 1,
					tokenlen(tokens + i + 1, tdelim));
		else if (tokens[i].type & (tdout))
			cmd.redirout[c2.redirout++] = concattokens(tokens + i + 1,
					tokenlen(tokens + i + 1, tdelim));
		else if (tokens[i].type & (td | twrd))
			cmd.argv[c2.argc++] = concattokens(tokens + i + 1,
					tokenlen(tokens + i + 1, tdelim));
	}
	return (cmd);
}

void	freecmd(t_cmd *cmd)
{
	size_t	i;

	i = -1;
	while (cmd->argv[++i])
		free(cmd->argv[i]);
	free(cmd->argv);
	i = -1;
	while (cmd->redirin[++i])
		free(cmd->redirin[i]);
	free(cmd->redirin);
	i = -1;
	while (cmd->redirout[++i])
		free(cmd->redirout[i]);
	free(cmd->redirout);
}
