/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:11:04 by francoma          #+#    #+#             */
/*   Updated: 2023/03/13 13:57:42 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

size_t	env_len(char **env);

static int	ft_strcmp_del(const char *s1, const char *s2, char del)
{
	int		diff;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	diff = 0;
	i = 0;
	while (!diff
		&& (s1[i] != '\0' || s2[i] != '\0')
		&& (s1[i] != del && s2[i] != del))
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (diff);
}

static int	is_same_var(char *v1, char *v2)
{
	return (ft_strcmp_del(v1, v2, '=') == 0);
}

static char	**append_env(char **env, char *var)
{
	size_t	len;
	char	**res;
	char	*tmp;

	len = env_len(env);
	res = malloc(sizeof(*res) * (len + 2));
	if (!res)
		return (ft_free_env(env));
	tmp = ft_strdup(var);
	if (!tmp)
	{
		free(res);
		return (ft_free_env(env));
	}
	ft_memcpy(res, env, sizeof(*env) * (len));
	res[len] = tmp;
	res[len + 1] = NULL;
	free(env);
	return (res);
}

char	**ft_update_env(char **env, char *var)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (env && env[i])
	{
		if (is_same_var(env[i], var))
		{
			tmp = ft_strdup(var);
			if (!tmp)
				return (ft_free_env(env));
			free(env[i]);
			env[i] = tmp;
			return (env);
		}
		i++;
	}
	return (append_env(env, var));
}

char	**ft_rm_env(char **env, char *var)
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
			res = ft_calloc(curr_len, sizeof(*res));
			if (!res)
				return (ft_free_env(env));
			free(env[i]);
			ft_memcpy(res, env, sizeof(*res) * i);
			ft_memcpy(res + i, env + i + 1, sizeof(*res) * (curr_len - i));
			free(env);
			break ;
		}
		i++;
	}
	return (res);
}
