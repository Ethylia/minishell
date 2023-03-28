/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:20:58 by francoma          #+#    #+#             */
/*   Updated: 2023/03/27 16:11:31 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include "data.h"
#include "env.h"
#include "util/util.h"
#include "wildcard.h"

char	getquote(t_token *token, char *q)
{
	if (token->type == tdqts && *q != '\'')
	{
		*q = '"' - *q;
		return (0);
	}
	if (token->type == tqts && *q != '"')
	{
		*q = '\'' - *q;
		return (0);
	}
	return (*q);
}

unsigned int	getnestlvl(t_token *token, unsigned int lvl)
{
	if (token->type == tpin)
		++lvl;
	if (token->type == tpout && lvl)
		--lvl;
	return (lvl);
}

size_t	tokenval(char *str, t_token *token, ssize_t *i)
{
	const char	*s;

	++(*i);
	if (token->type & (tqts | tdqts) && !token->quote)
		return (0);
	if (token->type == td && token->quote != '\'')
	{
		if ((++token)->type & twrd)
		{
			++(*i);
			s = get_varn(getdata()->local_env, token->val, token->len);
			if (!s)
				s = get_varn(getdata()->exported_env, token->val, token->len);
			if (s)
			{
				memcopy(str, s, strln(s));
				return (strln(s));
			}
			return (0);
		}
		return (1);
	}
	memcopy(str, token->val, token->len);
	return (token->len);
}

int	checksyntax(t_token *tokens)
{
	
}
