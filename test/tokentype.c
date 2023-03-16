/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:24:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/16 16:06:10 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include "util/util.h"

static enum e_tokens _gettoken2(char *line)
{
	if (line[0] == '(')
		return (tparenthesis_in);
	else if (line[0] == ')')
		return (tparenthesis_out);
	else if (line[0] == '"')
		return (tdouble_quote);
	else if (line[0] == '\'')
		return (tquote);
	else if (line[0] == '$')
		return (tdollar);
	return (tword);
}

enum e_tokens gettoken(char *line)
{
	if (line[0] == '|' && line[1] == '|')
		return (tor);
	else if (line[0] == '&' && line[1] == '&')
		return (tand);
	else if (line[0] == '|')
		return (tpipe);
	else if (line[0] == '<' && line[1] == '<')
		return (tredirin_heredoc);
	else if (line[0] == '>' && line[1] == '>')
		return (tredirout_append);
	else if (line[0] == '<')
		return (tredirin);
	else if (line[0] == '>')
		return (tredirout);
	else if (whitespace(line[0]))
		return (twhitespace);
	return (_gettoken2(line));
}
