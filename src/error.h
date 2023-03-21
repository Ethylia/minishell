/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:24 by francoma          #+#    #+#             */
/*   Updated: 2023/03/21 09:08:52 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SIG_INIT_ERROR_MSG "Minishell encountered a problem while \
initializing signal redirection.\n"

void	print_err(const char *problem);
void	exit_error(const char *problem);

#endif
