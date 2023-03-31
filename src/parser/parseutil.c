/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:44:21 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/31 10:14:19 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "token.h"
#include "cmd.h"
#include "util/util.h"
#include "wildcard.h"

static size_t	tokenlen(t_token *token, enum e_tokens delims)
{
	size_t	i;

	i = 0;
	if (token->type == tws)
		++i;
	while (token[i].type && (!(token[i].type & delims) || token[i].quote))
		++i;
	if (token[i].type == tws)
		++i;
	return (i);
}

int	toke(t_token *tokens, size_t *i, size_t *j)
{
	*j = tokenlen(tokens + *i
			+ !!(tokens[*i].type & (tdin | tdout | tapp | thdoc)), tdelim);
	if (!*j)
		return (1);
	return (0);
}
