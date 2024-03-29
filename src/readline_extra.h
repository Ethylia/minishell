/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_extra.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:41:51 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 16:58:15 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_EXTRA_H
# define READLINE_EXTRA_H

# include "util/vector.h"

void	rl_replace_line(const char *s, int clear_undo);
void	rl_clear_history(void);
void	get_path_executables(const char *s, int p, t_vector *vec);
char	**completion(const char *s, int start, int end);

#endif
