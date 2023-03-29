/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:09:15 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/29 16:29:54 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include "util/util.h"

t_token	*findnext(t_token *tokens, enum e_tokens type)
{
	while (tokens->type)
	{
		if (tokens->type & type && !tokens->quote)
			return (tokens);
		++tokens;
	}
	return (tokens);
}

static size_t	quotewrd(t_token *token)
{
	token->type = twrd;
	token->len = 1;
	return (1);
}

static size_t	createtoken(t_token *token, char *line, char q)
{
	size_t	i;

	token->len = 0;
	token->type = gettoken(line);
	token->val = line;
	if (token->type & tqts && (q == '"' || (!strchar(line + 1, '\'') && !q)))
		return (quotewrd(token));
	if (token->type & tdqts && (q == '\'' || (!strchar(line + 1, '\"') && !q)))
		return (quotewrd(token));
	if ((token->type == twrd && token->val[0] == '?')
		|| (token->type == twrd && token->val[0] == '$')
		|| (token->type == twrd && token->val[0] == '*'))
		return (token->len = 1);
	i = (token->type == thdoc || token->type == tapp
			|| token->type == tor || token->type == tand)
		+ !(token->type == tws || token->type == twrd);
	if (token->type != tws && token->type != twrd)
		return (token->len = i);
	while (line[i] && !(line[i] == '\'' && q == '\"') && !(line[i] == '*')
		&& !(line[i] == '\"' && q == '\'') && gettoken(line + i) == token->type)
		++i;
	return (token->len = i);
}

static size_t	counttokens(char *line)
{
	size_t			n;
	enum e_tokens	t;

	n = 0;
	while (line[0])
	{
		t = gettoken(line);
		if ((t == twrd && line[0] == '?') || (t == twrd && line[0] == '$')
			|| (t == twrd && line[0] == '*'))
		{
			++line;
			++n;
			continue ;
		}
		line += (t == thdoc || t == tapp
				|| t == tor || t == tand) + !(t == tws || t == twrd);
		if (t == tws || t == twrd)
			while (line[0] && line[0] != '*' && gettoken(line) == t)
				++line;
		++n;
	}
	return (n);
}

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	size_t	i[4];

	i[0] = counttokens(line);
	if (!i[0])
		return (0);
	tokens = malloc((i[0] + 1) * sizeof(t_token));
	if (!tokens)
		exit(EXIT_FAILURE);
	i[0] = -1;
	i[1] = 0;
	i[2] = '\0';
	i[3] = 0;
	while (line[i[1] + (++(i[0]) * 0)])
	{
		i[1] += createtoken(&tokens[i[0]], &line[i[1]], i[2]);
		tokens[i[0]].quote = getquote(&tokens[i[0]], (char *)(&i[2]));
		i[3] = getnestlvl(&tokens[i[0]], i[3]);
		tokens[i[0]].nestlvl = i[3];
	}
	tokens[i[0]].type = 0;
	return (tokens);
}
