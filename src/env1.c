/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:40:05 by francoma          #+#    #+#             */
/*   Updated: 2023/03/15 16:02:55 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "util/util.h"
#include "env.h"

size_t	env_len(char **env)
{
	size_t	len;

	len = 0;
	if (!env)
		return (len);
	while (env[len])
		len++;
	return (len);
}

char	**copy_env(char **env)
{
	char	**res;
	size_t	len;
	size_t	i;

	len = env_len(env);
	if (!len)
		return (NULL);
	res = malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (NULL);
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

char	**free_env(char **env)
{
	size_t	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (NULL);
}
