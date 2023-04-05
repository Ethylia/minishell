/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenvalidation2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:16:08 by francoma          #+#    #+#             */
/*   Updated: 2023/04/04 11:40:02 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenvalidation.h"

int	is_type(t_token *token, enum e_tokens type)
{
	return (token->type & type && !token->quote);
}

int	is_word(t_token *token)
{
	if (token->type == twrd)
		return (1);
	else if (token->type == td)
		return ((token + 1)->type == td || is_word(token + 1));
	else if (token->type & (tqts | tdqts))
		return (1);
	return (0);
}

int	next_to_word(t_token *tokens)
{
	size_t	i;

	i = 1;
	i += (tokens[i].type == tws);
	return (is_word(&tokens[i]));
}

int	next_to_redir(t_token *tokens)
{
	size_t	i;

	i = 1;
	i += (tokens[i].type == tws);
	return (is_redir(&tokens[i]));
}

int	next_to(t_token *tokens, enum e_tokens type)
{
	size_t	i;

	i = 1;
	i += (tokens[i].type == tws);
	return (tokens[i].type == type && !tokens[i].quote);
}
