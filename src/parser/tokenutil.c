/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:20:58 by francoma          #+#    #+#             */
/*   Updated: 2023/03/21 13:29:46 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

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
