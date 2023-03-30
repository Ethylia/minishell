/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:28:31 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 09:43:25 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
