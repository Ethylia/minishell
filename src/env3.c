/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:28:31 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 10:59:54 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util/util.h"
#include "data.h"
#include "env.h"

static unsigned int	atoui(const char *str)
{
	unsigned int	nb;

	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb);
}

void	update_shlvl(void)
{
	const char	*curr_shlvl;
	char		*shlvl;
	char		*tmp;


	curr_shlvl = get_var(getdata()->exported_env, "SHLVL");
	if (!curr_shlvl)
		shlvl = "SHLVL=1";
	else
	{
		tmp = intoa(atoui(curr_shlvl) + 1);
		shlvl = concatstr(2, "SHLVL=", tmp);
		free(tmp);
		update_env(&(getdata()->exported_env), shlvl);
		free(shlvl);
	}
}

int	is_same_var(char const *v1, char const *v2)
{
	return (strcmp_del(v1, v2, '=') == 0);
}

int	is_append_var(char const *v1, char const *v2)
{
	size_t	i;

	i = 0;
	while (v1[i] && v2[i])
	{
		if (v1[i] == '='
			&& (v2[i] == '+' && v2[i + 1] == '='))
			return (1);
		if (v1[i] != v2[i])
			return (0);
		i++;
	}
	return (0);
}

