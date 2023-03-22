/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:22:04 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 14:29:31 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define BUILTIN_ECHO "echo"
# define BUILTIN_CD "cd"
# define BUILTIN_PWD "pwd"
# define BUILTIN_EXPORT "export"
# define BUILTIN_UNSET "unset"
# define BUILTIN_ENV "env"
# define BUILTIN_EXIT "exit"

# include "../parser/cmd.h"

typedef int		(*t_builtin_func)(const int, char *const[], char **);
int				bi_echo(const int argc, char *const argv[], char **envp);
int				bi_cd(const int argc, char *const argv[], char **envp);
int				bi_pwd(const int argc, char *const argv[], char **envp);
int				bi_export(const int argc, char *const argv[], char **envp);
int				bi_unset(const int argc, char *const argv[], char **envp);
int				bi_env(const int argc, char *const argv[], char **envp);
int				bi_exit(const int argc, char *const argv[], char **envp);
int				bi_heredoc(const char *eof);

const char		**get_builtins_names(void);
t_builtin_func	get_builtin_func(size_t i);
int				is_builtin(t_cmd *cmd);
int				exec_builtin(t_cmd *cmd);


#endif
