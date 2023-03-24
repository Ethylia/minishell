/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:54:39 by francoma          #+#    #+#             */
/*   Updated: 2023/03/24 14:59:36 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "parser/cmd.h"

typedef struct s_data
{
	char	**exported_env;
	char	**local_env;
	t_token	*tokens;
	t_cmd	cmd;
	int		isinteractive;
}	t_data;

t_data	*getdata(void);
void	freedata(void);

#endif
