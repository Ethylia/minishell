/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:05:10 by francoma          #+#    #+#             */
/*   Updated: 2023/03/21 13:57:05 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include <unistd.h>
# include <fcntl.h>

# define NO_FILE -1
// redir output mode is defined by umask
//	the mask 0022 gives the mode 0755
# define REDIROUT_MODE S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH

int	redir_input(t_cmd *cmd, t_pipe *prev_pipe);
int	redir_output(t_cmd *cmd, t_pipe *next_pipe);

#endif
