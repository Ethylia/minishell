/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenvalidation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:04:07 by francoma          #+#    #+#             */
/*   Updated: 2023/03/28 14:15:00 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENVALIDATION_H
# define TOKENVALIDATION_H

# include "token.h"

t_token	*unexpected_token(t_token *tokens);
void	print_unexpected_token(t_token *t);

int		is_redir(t_token *token);
int		is_word(t_token *token);
int		next_to_word(t_token *tokens);
int		next_to_redir(t_token *tokens);
int		next_to(t_token *tokens, enum e_tokens type);

#endif
