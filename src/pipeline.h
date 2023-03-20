/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:21:21 by francoma          #+#    #+#             */
/*   Updated: 2023/03/20 17:35:09 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "parser/cmd.h"

int		is_pipeline_end(t_cmd *cmd);
void	close_pipe(t_pipe *p);
void	read_pipe(t_pipe *p);
void	write_pipe(t_pipe *p);
int		pipeline(t_cmd *cmd, t_pipe *prev_pipe);

#endif
