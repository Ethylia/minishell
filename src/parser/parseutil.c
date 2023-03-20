/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:44:21 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/20 14:18:21 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "token.h"

int	toke(t_token *tokens, size_t *i, size_t *j)
{
	*j = tokenlen(tokens + *i + !!(tokens[*i].type & (tdin | tdout)), tdelim);
	if (!*j)
	{
		++i[0];
		return (1);
	}
	return (0);
}
