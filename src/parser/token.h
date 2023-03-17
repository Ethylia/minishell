/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:06:01 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/17 10:44:11 by eboyce-n         ###   ########.fr       */
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
	twrd = 1 << 13
};

typedef struct s_token
{
	const char		*val;
	size_t			len;
	enum e_tokens	type;
}	t_token;


enum e_tokens	gettoken(const char *line);
t_token			*tokenize(char *line);
t_token			*findnext(t_token *tokens, enum e_tokens type);
t_token			*findafter(t_token *tokens, enum e_tokens type);

#endif
