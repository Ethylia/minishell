/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenvalidation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:04:07 by francoma          #+#    #+#             */
/*   Updated: 2023/04/04 11:34:12 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENVALIDATION_H
# define TOKENVALIDATION_H

# include "token.h"

size_t	skip_ws_pin(t_token *tokens);
int		all_parenthesis_closed(t_token *t);
size_t	count_tokens(t_token *t);

int		is_type(t_token *token, enum e_tokens type);
int		is_redir(t_token *token);
int		is_word(t_token *token);
int		next_to_word(t_token *tokens);
int		next_to_redir(t_token *tokens);
int		next_to(t_token *tokens, enum e_tokens type);

#endif
