/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:24:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/22 16:48:30 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include "util/util.h"
#include "env.h"
#include "data.h"
#include "wildcard.h"

size_t	wildchars(t_token *token, size_t *len)
{
	if (token->type == twrd && !token->quote)
	{
		wildcard
		return (1);
	}
	*len += token->len;
	return (1);
}

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
	return (wildchars(token, len));
	*len += token->len;
	return (1);
}

char	*concattokens(t_token *tokens, ssize_t len)
{
	char	*str;
	size_t	strlen;
	ssize_t	i[2];

	i[0] = -1;
	i[1] = 0;
	strlen = 0;
	if (tokens->type & tws)
		++i[0];
	while (++i[0] < len && !(tokens[i[0]].type & tws && !tokens[i[0]].quote))
		if (!(tokens[i[0]].type & (tqts | tdqts) && !tokens[i[0]].quote))
			i[0] += tokenchars(&tokens[i[0]], &strlen) - 1;
	str = malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (0);
	i[0] = 0 + (tokens->type & tws);
	while (i[0] < len && !(tokens[i[0]].type & tws && !tokens[i[0]].quote))
		i[1] += tokenval(str + i[1], &tokens[i[0]], &i[0]);
	str[i[1]] = 0;
	return (str);
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
