/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:30:34 by francoma          #+#    #+#             */
/*   Updated: 2023/03/16 16:19:44 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

const char* const tokens[] =
{
	"tquote",
	"tdouble_quote",
    "tand",
	"tor",
    "tparenthesis_in",
    "tparenthesis_out",
	"tpipe",
	"tdollar",
	"tredirin",
	"tredirin_heredoc",
	"tredirout",
	"tredirout_append",
	"twhitespace",
	"tword"
};

int main(void)
{
	t_token	*token = tokenize("echo \"he&l$woolo world\" || (echo \"hello world\" && echo (\"hello world\"))");
	for(t_token *i = token; i; i = i->next)
	{
		printf("type: %-16s, value: %-10.*s, len: %zu\n", tokens[i->type], (int)i->len, i->val, i->len);
	}
	return (0);
}
