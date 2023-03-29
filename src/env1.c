/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:40:05 by francoma          #+#    #+#             */
/*   Updated: 2023/03/29 16:05:43 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "util/util.h"
#include "env.h"

size_t	env_len(const char **env)
{
	size_t	len;

	len = 0;
	if (!env)
		return (len);
	while (env[len])
		len++;
	return (len);
}

char	**copy_env(const char **env)
{
	char	**res;
	size_t	len;
	size_t	i;

	len = env_len(env);
	if (!len)
		return (NULL);
	res = malloc(sizeof(*res) * (len + 1));
	if (!res)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		res[i] = strdupe(env[i]);
		if (!res[i])
			free_env(res);
		i++;
	}
	res[len] = NULL;
	return (res);
}

void	print_env(char *const env[])
{
	if (!env)
		return ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

void	free_env(char **env)
{
	size_t	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	env = NULL;
}

char const	*get_varn(char *const envp[], char const *var, size_t l)
{
	size_t	i;
	char	*tmp;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		tmp = malloc(sizeof(*tmp) * (l + 1));
		if (!tmp)
			exit(EXIT_FAILURE);
		memcopy(tmp, var, l);
		tmp[l] = '\0';
		if (is_same_var(envp[i], tmp))
		{
			free(tmp);
			return (envp[i] + strln_del(envp[i], '=') + 1);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	**env;

// 	env = copy_env((const char **)envp);
// 	update_env(&env, "PWD=OK");
// 	printf("%s\n", get_var(env, "PWD"));
// }
