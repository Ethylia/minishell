/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:05:10 by francoma          #+#    #+#             */
/*   Updated: 2023/03/23 10:26:39 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include <unistd.h>
# include <fcntl.h>

# define NO_FILE -1
// redir output mode is defined by umask
//	e.g. the mask 0022 gives the mode 0755
# define REDIROUT_MODE 0755

int	redir_input(t_cmd *cmd, t_pipe *prev_pipe);
int	redir_output(t_cmd *cmd, t_pipe *next_pipe);

#endif
