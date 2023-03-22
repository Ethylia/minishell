/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:22:04 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 07:22:56 by eboyce-n         ###   ########.fr       */
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

int	is_builtin(t_cmd *cmd);
int	exec_builtin(t_cmd *cmd);

typedef int	(*t_builtin_func)(const int, char *const[], char *const[]);
int	echo(const int argc, char *const argv[], char *const envp[]);
int	cd(const int argc, char *const argv[], char *const envp[]);
int	pwd(const int argc, char *const argv[], char *const envp[]);
int	export(const int argc, char *const argv[], char *const envp[]);
int	unset(const int argc, char *const argv[], char *const envp[]);
int	env(const int argc, char *const argv[], char *const envp[]);
int	bi_exit(const int argc, char *const argv[], char *const envp[]);
int	bi_heredoc(const char *eof);

#endif
