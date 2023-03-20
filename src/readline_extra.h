/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_extra.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:41:51 by francoma          #+#    #+#             */
/*   Updated: 2023/03/20 11:42:38 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_EXTRA_H
# define READLINE_EXTRA_H

void	rl_replace_line(const char *s, int clear_undo);
void	rl_clear_history(void);

#endif
