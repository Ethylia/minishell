/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:06:01 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/16 16:07:14 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <stdio.h>

enum e_tokens
{
	tquote,
	tdouble_quote,
    tand,
	tor,
    tparenthesis_in,
    tparenthesis_out,
	tpipe,
	tdollar,
	tredirin,
	tredirin_heredoc,
	tredirout,
	tredirout_append,
	twhitespace,
	tword,
};

typedef struct s_token
{
	char			*val;
	size_t			len;
	struct s_token	*next;
	enum e_tokens	type;
}	t_token;


enum e_tokens gettoken(char *line);
t_token		*tokenize(char *line);

#endif
