/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:06:01 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/24 10:59:45 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <stdio.h>

enum e_tokens
{
	tqts = 1 << 0,
	tdqts = 1 << 1,
	tand = 1 << 2,
	tor = 1 << 3,
	tpin = 1 << 4,
	tpout = 1 << 5,
	tpipe = 1 << 6,
	td = 1 << 7,
	tdin = 1 << 8,
	thdoc = 1 << 9,
	tdout = 1 << 10,
	tapp = 1 << 11,
	tws = 1 << 12,
	twrd = 1 << 13,
	tdelim = tand | tor | tpipe | tdin | thdoc
	| tdout | tapp | tws | tpin | tpout
};
	typedef struct s_token
{
	const char *val;
	size_t len;
	enum e_tokens type;
	unsigned int nestlvl;
	unsigned char quote;
}	t_token;

enum e_tokens	gettoken(const char *line);
t_token			*tokenize(char *line);
t_token			*findnext(t_token *tokens, enum e_tokens type);
char			*concattokens(t_token *tokens, ssize_t len);
unsigned int	getnestlvl(t_token *token, unsigned int lvl);
char			getquote(t_token *token, char *q, const char *line);
size_t			tokenval(char *str, t_token *token, ssize_t *i);

#endif
