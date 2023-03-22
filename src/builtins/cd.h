/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:34:56 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 14:09:59 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

void	print_path(char *const envp[], const char *path);
void	updateps1(const char *path);
int		update_oldpwd(char **envp);
int		update_pwd(char **envp);

#endif
