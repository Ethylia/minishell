/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:29:26 by francoma          #+#    #+#             */
/*   Updated: 2023/03/20 13:51:30 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "../util/util.h"
#include "../def.h"

int	bi_heredoc(const char *eof)
{
	char	*line;
	
	while (1)
	{
		line = readline(HEREDOC_PS);
		if (!line || strcmp(line, eof) == 0)
			break ;
		printf("%s\n", line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
