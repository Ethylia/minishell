/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:43:24 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 14:57:56 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

size_t	count_wildcard_values(const char *wildcard);
int		matches_wildcard(const char *wildcard, const char *candidate);
char	**wildcard_values(const char *wildcard);
void	free_wildcard_values(char **wildcard_values);

#endif
