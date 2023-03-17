/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:09:15 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/17 10:43:44 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include "util/util.h"

t_token	*findnext(t_token *tokens, enum e_tokens type)
{
	while (tokens->type)
	{
		if (tokens->type & type)
			return (tokens);
		++tokens;
	}
	return (0);
}

t_token	*findafter(t_token *tokens, enum e_tokens type)
{
	while (tokens->type)
	{
		if (tokens->type & type)
			return (tokens + 1);
		++tokens;
	}
	return (tokens);
}

static size_t	createtoken(t_token *token, char *line)
{
	size_t	i;

	token->len = 0;
	token->type = gettoken(line);
	i = (token->type == thdoc || token->type == tapp
			|| token->type == tor || token->type == tand)
		+ !(token->type == tws || token->type == twrd);
	token->val = line + i;
	if (token->type != tws && token->type != twrd)
		return (i);
	while (line[i])
	{
		if (gettoken(line + i) != token->type)
			break ;
		++i;
	}
	token->len = i;
	return (i);
}

static size_t	counttokens(char *line)
{
	size_t			n;
	enum e_tokens	t;

	n = 0;
	while (line[0])
	{
		t = gettoken(line);
		line += (t == thdoc || t == tapp
				|| t == tor || t == tand) + !(t == tws || t == twrd);
		if (t == tws || t == twrd)
			while (line[0] && gettoken(line) == t)
				++line;
		++n;
	}
	return (n);
}

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	size_t	i;

	i = counttokens(line);
	if (!i)
		return (0);
	tokens = malloc((i + 1) * sizeof(t_token));
	if (!tokens)
		return (0);
	i = 0;
	while (line[0])
		line += createtoken(&tokens[i++], line);
	tokens[i].type = 0;
	return (tokens);
}
