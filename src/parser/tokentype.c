/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:24:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/22 10:11:38 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include "util/util.h"
#include "env.h"
#include "data.h"

size_t	tokenchars(t_token *token, size_t *len)
{
	const char	*s = 0;

	if (token->type == td && !token->quote)
	{
		if ((++token)->type & twrd)
		{
			s = get_var(getdata()->local_env, token->val);
			if (!s)
				s = get_var(getdata()->exported_env, token->val);
			if (s)
				*len += strln(s);
			return (2);
		}
		++(*len);
		return (1);
	}
	*len += token->len;
	return (1);
}

char	*concattokens(t_token *tokens, size_t len)
{
	char	*str;
	size_t	strlen;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	strlen = 0;
	if (tokens->type & tws)
		++i;
	while (i < len && !(tokens[i].type & tws && !tokens[i].quote))
	{
		if (!(tokens[i].type & (tqts | tdqts) && !tokens[i].quote))
			i += tokenchars(&tokens[i], &strlen);
		else
			++i;
	}
	str = malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (0);
	i = 0 + (tokens->type & tws);
	while (i < len && !(tokens[i].type & tws && !tokens[i].quote))
		j += tokenval(str + j, &tokens[i], &i);
	str[j] = 0;
	return (str);
}

size_t	tokenlen(t_token *token, enum e_tokens delims)
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

static enum e_tokens	_gettoken2(const char *line)
{
	if (line[0] == '(')
		return (tpin);
	else if (line[0] == ')')
		return (tpout);
	else if (line[0] == '"')
		return (tdqts);
	else if (line[0] == '\'')
		return (tqts);
	else if (line[0] == '$')
		return (td);
	return (twrd);
}

enum e_tokens	gettoken(const char *line)
{
	if (line[0] == '|' && line[1] == '|')
		return (tor);
	else if (line[0] == '&' && line[1] == '&')
		return (tand);
	else if (line[0] == '|')
		return (tpipe);
	else if (line[0] == '<' && line[1] == '<')
		return (thdoc);
	else if (line[0] == '>' && line[1] == '>')
		return (tapp);
	else if (line[0] == '<')
		return (tdin);
	else if (line[0] == '>')
		return (tdout);
	else if (is_ws(line[0]))
		return (tws);
	return (_gettoken2(line));
}
