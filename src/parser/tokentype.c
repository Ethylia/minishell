/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:24:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/17 09:37:50 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include "util/util.h"

static enum e_tokens _gettoken2(const char *line)
{
	if (line[0] == '(')
		return (tpin);
	else if (line[0] == ')')
		return (tpout);
	else if (line[0] == '"')
		return (tdqts);
	else if (line[0] == '\'')
		return (tqts);
	else if (line[0] == '$')
		return (td);
	return (twrd);
}

enum e_tokens gettoken(const char *line)
{
	if (line[0] == '|' && line[1] == '|')
		return (tor);
	else if (line[0] == '&' && line[1] == '&')
		return (tand);
	else if (line[0] == '|')
		return (tpipe);
	else if (line[0] == '<' && line[1] == '<')
		return (thdoc);
	else if (line[0] == '>' && line[1] == '>')
		return (tapp);
	else if (line[0] == '<')
		return (tdin);
	else if (line[0] == '>')
		return (tdout);
	else if (whitespace(line[0]))
		return (tws);
	return (_gettoken2(line));
}
