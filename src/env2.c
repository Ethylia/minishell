/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:11:04 by francoma          #+#    #+#             */
/*   Updated: 2023/03/29 16:06:26 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util/util.h"
#include "env.h"

size_t	env_len(const char **env);

int	is_same_var(char const *v1, char const *v2)
{
	return (strcmp_del(v1, v2, '=') == 0);
}

static void	append_env(char ***env, const char *var)
{
	size_t	len;
	char	**res;
	char	*tmp;

	len = env_len((const char **)*env);
	res = malloc(sizeof(*res) * (len + 2));
	if (!res)
		exit(EXIT_FAILURE);
	tmp = strdupe(var);
	memcopy(res, *env, sizeof(*res) * (len));
	res[len] = tmp;
	res[len + 1] = NULL;
	free(*env);
	*env = res;
}

void	update_env(char ***env, const char *var)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (*env && (*env)[i])
	{
		if (is_same_var((*env)[i], var))
		{
			tmp = strdupe(var);
			if (!tmp)
			{

			}
			free((*env)[i]);
			(*env)[i] = tmp;
			return ;
		}
		i++;
	}
	append_env(env, var);
}

void	rm_env(char ***env, char *var)
{
	size_t	i;
	size_t	curr_len;
	char	**res;

	i = 0;
	while (*env && (*env)[i] && !is_same_var((*env)[i], var))
		i++;
	if (!*env || !(*env)[i])
		return ;
	curr_len = env_len((const char **)(*env));
	res = malloc(sizeof(*res) * curr_len);
	if (!res)
		exit(EXIT_FAILURE);
	free((*env)[i]);
	memcopy(res, *env, sizeof(*res) * i);
	memcopy(res + i, *env + i + 1, sizeof(*res) * (curr_len - i - 1));
	res[curr_len - 1] = NULL;
	free(*env);
	*env = res;
}

char const	*get_var(char *const envp[], char const *var)
{
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (is_same_var(envp[i], var))
			return (envp[i] + strln_del(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}
