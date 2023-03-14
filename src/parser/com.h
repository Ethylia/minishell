/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:33:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/14 15:53:52 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMTREE_H
# define COMTREE_H

# include <stddef.h>

#pragma pack(1)
typedef struct s_pipe
{
	int	out;
	int in;
}	t_pipe;

typedef struct s_com
{
	t_com	*pipe;
	char	*com;
	char	**redirin;
	char	**redirout;
}	t_com;

t_com	buildcoms(char *line);

#endif
