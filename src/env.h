/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:18:16 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 10:42:28 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stddef.h>

void		update_env(char ***env, const char *var);
void		append_var(char ***env, char *var);
void		append_env(char ***env, const char *var);
void		rm_env(char ***env, char *var);
char		**copy_env(const char **env);
void		print_env(char *const env[]);
void		free_env(char **env);
int			is_same_var(char const *v1, char const *v2);
int			is_append_var(char const *v1, char const *v2);
char const	*get_var(char *const envp[], char const *var);
char const	*get_varn(char *const envp[], char const *var, size_t l);
void		update_shlvl(void);

#endif
