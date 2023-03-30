/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:23:54 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 13:20:21 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline_extra.h"
#include "util/vector.h"
#include "util/util.h"
#include "builtins/builtins.h"
#include "def.h"

char	**completion(const char *s, int start, int end)
{
	t_vector	res;
	char		*tmp;
	size_t		i;

	if (end - start <= 0 || !s)
		return (NULL);
	i = -1;
	v_init(&res, sizeof(char *), 8);
	while (get_builtins_names()[++i])
	{
		if (!strncmp(get_builtins_names()[i], s, end - start))
		{
			tmp = strdupe(get_builtins_names()[i]);
			v_push(&res, &tmp);
		}
	}
	if (res.size)
	{
		v_push(&res, NULLPTR);
		return ((char **)res.data);
	}
	free(res.data);
	return (NULL);
}
