/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:57:50 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/16 16:54:41 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "env.h"

int	main(__attribute__((unused))int argc,
	__attribute__((unused))char **argv, char **env)
{
	char	*line;
	char	*path;

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
