/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:18:16 by francoma          #+#    #+#             */
/*   Updated: 2023/03/15 16:24:44 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

char		**update_env(char **env, char *var);
char		**rm_env(char **env, char *var);
char		**copy_env(char **env);
void		print_env(char *const env[]);
char		**free_env(char **env);
char const	*get_var(char *const envp[], char const *var);

char		***get_exported_env(void);
void		set_exported_env(char *env[]);
char		***get_local_env(void);

#endif
