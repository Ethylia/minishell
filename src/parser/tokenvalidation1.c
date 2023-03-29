/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenvalidation1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:16:08 by francoma          #+#    #+#             */
/*   Updated: 2023/03/29 09:58:53 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenvalidation.h"

size_t	skip_ws_pin(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i].type == tws || tokens[i].type == tpin)
		i++;
	return (i);
}

int	all_parenthesis_closed(t_token *t)
{
	size_t	in_count;
	size_t	out_count;

	in_count = 0;
	out_count = 0;
	while (t->type)
	{
		if (t->type == tpin && !t->quote)
			in_count++;
		else if (t->type == tpout && !t->quote)
			out_count++;
		t++;
	}
	return (in_count == out_count);
}

size_t	count_tokens(t_token *t)
{
	size_t	i;

	i = 0;
	while (t[i].type)
		i++;
	return (i);
}
