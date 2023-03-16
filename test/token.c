/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:09:15 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/16 16:47:59 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include "util/util.h"

static size_t	createtoken(t_token *token, const char *line)
{
	size_t	i;

	token->len = 0;
	token->next = 0;
	token->type = gettoken(line);
	i = (token->type == tredirin_heredoc || token->type == tredirout_append
		|| token->type == tor || token->type == tand)
			+ !(token->type == twhitespace || token->type == tword);
	token->val = line + i;
	if (token->type != twhitespace && token->type != tword)
		return i;
	while (line[i])
	{
		if (gettoken(line + i) != token->type)
			break ;
		++i;
	}
	token->len = i;
	return (i);
}

t_token	*tokenize(const char *line)
{
	t_token	*token;
	t_token	*head;

	token = malloc(sizeof(t_token));
	head = token;
	while (line[0])
	{
		line += createtoken(token, line);
		if (line[0])
		{
			token->next = malloc(sizeof(t_token));
			token = token->next;
		}
	}
	return (head);
}
