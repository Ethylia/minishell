/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:18:16 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 07:40:24 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

char		**update_env(char **env, const char *var);
char		**rm_env(char **env, char *var);
char		**copy_env(const char **env);
void		print_env(char *const env[]);
char		**free_env(char **env);
char const	*get_var(char *const envp[], char const *var);

#endif
