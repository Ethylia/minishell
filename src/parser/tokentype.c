/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:24:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/28 16:14:27 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include "util/util.h"
#include "env.h"
#include "data.h"
#include "wildcard.h"

// static size_t	tokenchars(t_token *token, size_t *len)
// {
// 	const char	*s = 0;

// 	if (token->type == td && token->quote != '\'')
// 	{
// 		if ((++token)->type & twrd)
// 		{
// 			s = get_varn(getdata()->local_env, token->val, token->len);
// 			if (!s)
// 				s = get_varn(getdata()->exported_env, token->val, token->len);
// 			if (s)
// 				*len += strln(s);
// 			return (2);
// 		}
// 		++(*len);
// 		return (1);
// 	}
// 	*len += token->len;
// 	return (1);
// }

char	*concattokens(t_token *tokens, size_t *len)
{
	size_t		i;
	size_t		j;
	t_vector	vec;

	i = -1;
	v_init(&vec, sizeof(char), 16);
	while (tokens[++i].type)
	{
		if (tokens[i].type & tdelim && !tokens[i].quote)
			break ;
		++(*len);
		j = -1;
		while (++j < tokens[i].len)
			v_push(&vec, tokens[i].val + j);
	}
	v_push(&vec, "\0");
	return ((char *)vec.data);
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
