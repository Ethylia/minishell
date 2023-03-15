/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/15 15:11:14 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "env.h"

int	main(__attribute__((unused))int argc,
	__attribute__((unused))char *argv[], char *envp[])
{
	char	*line;
	char	*path;

	set_exported_env(envp);
	path = getenv("PATH");
	printf("PATH: %s\n", path);
	line = readline("msh$ ");
	while (line)
	{
		printf("%s\n", line);
		if (*line)
			add_history(line);
		free(line);
		line = readline("msh$ ");
	}
	printf("\n");
}
