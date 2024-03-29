/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:59:49 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 14:02:16 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "util/util.h"
#include "wildcard.h"

void	free_wildcard_values(char **wildcard_values)
{
	size_t			i;

	i = 0;
	if (!wildcard_values)
		return ;
	while (wildcard_values[i])
	{
		free(wildcard_values[i]);
		i++;
	}
	free(wildcard_values);
}

size_t	count_wildcard_values(const char *wildcard)
{
	DIR				*folder;
	struct dirent	*entry;
	size_t			count;

	folder = opendir(".");
	if (!folder)
		return (0);
	count = 0;
	while (1)
	{
		entry = readdir(folder);
		if (!entry)
			break ;
		count += matches_wildcard(wildcard, entry->d_name);
	}
	closedir(folder);
	return (count);
}

size_t	wildlen(const char *const *wildcard)
{
	size_t			len;

	len = 0;
	while (wildcard[len])
		len++;
	return (len);
}

typedef struct s_wildcard_values
{
	DIR				*folder;
	struct dirent	*entry;
	char			**res;
	size_t			count;
	size_t			i;
}	t_wildcard_values;

static void	wildcard_values_loop(t_wildcard_values *var, const char *wildcard)
{
	while (1)
	{
		var->entry = readdir(var->folder);
		if (!var->entry)
			break ;
		if (matches_wildcard(wildcard, var->entry->d_name))
		{
			var->res[var->i] = concatstr(1, var->entry->d_name);
			if (!var->res[var->i])
			{
				free_wildcard_values(var->res);
				var->res = NULL;
				break ;
			}
			var->i++;
		}
	}
}

// Must free return with free_wildcard_values
char	**wildcard_values(const char *wildcard)
{
	t_wildcard_values	var;

	var.count = count_wildcard_values(wildcard);
	var.res = malloc(sizeof(*var.res) * (var.count + 1));
	if (!var.res)
		exit(EXIT_FAILURE);
	var.res[var.count] = NULL;
	var.i = 0;
	var.folder = opendir(".");
	if (!var.folder)
	{
		free(var.res);
		return (NULL);
	}
	wildcard_values_loop(&var, wildcard);
	closedir(var.folder);
	return (var.res);
}

// // gcc wildcard.c wildcard2.c util/*.c
// #include <stdio.h>
// int main(int argc, char const *argv[])
// {
// 	char	**res;
// 	size_t	i;

// 	if (argc == 1)
// 	{
// 		printf("wildcard is first arg\n");
// 		return (0);
// 	}
// 	res = wildcard_values(argv[1]);
// 	i = 0;
// 	while (res[i])
// 	{
// 		printf("%s ", res[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	free_wildcard_values(res);
// 	return (0);
// }
