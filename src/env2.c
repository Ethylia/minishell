/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:11:04 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 11:26:10 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util/util.h"
#include "env.h"

size_t	env_len(const char **env);

static char	*remove_plus(const char *var)
{
	size_t	i;
	int		removed_plus;

	removed_plus = 0;
	i = 0;
	while (var[i] && var[i] != '+' && var[i + 1] != '=')
		i++;
	return (concatstr_ln(2, var, i, var + i + 1, strln(var + i + 1)));
}

void	append_env(char ***env, const char *var)
{
	size_t	len;
	char	**res;
	char	*tmp;

	len = env_len((const char **)*env);
	res = malloc(sizeof(*res) * (len + 2));
	if (!res)
		exit(EXIT_FAILURE);
	if (strchar(var, '+') && strchar(var, '+')[1] == '=')
		tmp = remove_plus(var);
	else
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
			free((*env)[i]);
			(*env)[i] = tmp;
			return ;
		}
		else if (is_append_var((*env)[i], var))
		{
			tmp = concatstr(2, (*env)[i], strchar(var, '+') + 2);
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
