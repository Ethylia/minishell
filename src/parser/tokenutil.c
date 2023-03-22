/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:20:58 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 16:03:49 by francoma         ###   ########.fr       */
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

size_t	copywilds(char *str, char **wilds)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (wilds[++i])
	{
		memcopy(str + j, wilds[i], strln(wilds[i]));
		j += strln(wilds[i]) + !!(wilds[i + 1]);
		if (!wilds[i + 1])
			str[j - 1] = ' ';
	}
	return (j);
}

size_t	wildval(char *str, t_token *token)
{
	char	**s;
	size_t	j;

	if (token->type == twrd && !token->quote && strchar(str, '*'))
	{
		s = wildcard_values(str);
		if (!s || !s[0])
		{
			free_wildcard_values(s);
			memcopy(str, token->val, token->len);
			return (token->len);
		}
		j = copywilds(str, s);
		return (j);
	}
	memcopy(str, token->val, token->len);
	return (token->len);
}

size_t	tokenval(char *str, t_token *token, size_t *i)
{
	const char	*s;

	++(*i);
	if (token->type == td)
	{
		if ((++token)->type & twrd)
		{
			++(*i);
			s = get_var(getdata()->local_env, token->val);
			if (!s)
				s = get_var(getdata()->exported_env, token->val);
			if (s)
			{
				memcopy(str, s, strln(s));
				return (strln(s));
			}
			return (0);
		}
		return (1);
	}
	return (wildval(str, token));
}
