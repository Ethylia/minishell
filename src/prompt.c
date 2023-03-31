/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:05:18 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/31 10:02:18 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <readline/readline.h>
#include "data.h"
#include "env.h"
#include "util/util.h"

void	togglectl(int boolean)
{
	struct termios	term;

	if (tcgetattr(STDOUT_FILENO, &term) == -1)
		return ;
	if (boolean)
		term.c_lflag |= (ECHOCTL);
	else
		term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}

char	*displayprompt(void)
{
	char	*line;

	if (!(getdata()->isinteractive))
	{
		line = readline("");
		rl_already_prompted = 0;
		return (line);
	}
	togglectl(0);
	line = readline(get_var(getdata()->local_env, "PS1"));
	rl_already_prompted = 0;
	togglectl(1);
	return (line);
}
