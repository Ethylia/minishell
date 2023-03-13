/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:11:04 by francoma          #+#    #+#             */
/*   Updated: 2023/03/13 15:34:22 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util/util.h"
#include "env.h"

size_t	env_len(char **env);

static int	is_same_var(char *v1, char *v2)
{
	return (strcmp_del(v1, v2, '=') == 0);
}

static char	**append_env(char **env, char *var)
{
	size_t	len;
	char	**res;
	char	*tmp;

	len = env_len(env);
	res = malloc(sizeof(*res) * (len + 2));
	if (!res)
		return (free_env(env));
	tmp = strdup(var);
	if (!tmp)
	{
		free(res);
		return (free_env(env));
	}
	memcpy(res, env, sizeof(*env) * (len));
	res[len] = tmp;
	res[len + 1] = NULL;
	free(env);
	return (res);
}

char	**update_env(char **env, char *var)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (env && env[i])
	{
		if (is_same_var(env[i], var))
		{
			tmp = strdup(var);
			if (!tmp)
				return (free_env(env));
			free(env[i]);
			env[i] = tmp;
			return (env);
		}
		i++;
	}
	return (append_env(env, var));
}

char	**rm_env(char **env, char *var)
{
	size_t	i;
	size_t	curr_len;
	char	**res;

	res = env;
	i = 0;
	while (env && env[i])
	{
		if (is_same_var(env[i], var))
		{
			curr_len = env_len(env);
			res = malloc(sizeof(*res) * curr_len);
			if (!res)
				return (free_env(env));
			free(env[i]);
			memcpy(res, env, sizeof(*res) * i);
			memcpy(res + i, env + i + 1, sizeof(*res) * (curr_len - i));
			res[curr_len - 1] = NULL;
			free(env);
			break ;
		}
		i++;
	}
	return (res);
}
