/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:40:05 by francoma          #+#    #+#             */
/*   Updated: 2023/03/13 14:38:53 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**ft_copy_env(char **env)
{
	char	**res;
	size_t	len;
	size_t	i;

	len = env_len(env);
	if (!len)
		return (NULL);
	res = ft_calloc(len, sizeof(*res));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		res[i] = ft_strdup(env[i]);
		if (!res[i])
			ft_free_env(res);
		i++;
	}
	return (res);
}

void	ft_print_env(char *env[])
{
	if (!env)
		return ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

void	*free_env(char **env)
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
	return (NULL);
}
