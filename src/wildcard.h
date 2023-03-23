/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:43:24 by francoma          #+#    #+#             */
/*   Updated: 2023/03/23 09:09:59 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

size_t	count_wildcard_values(const char *wildcard);
int		matches_wildcard(const char *wildcard, const char *candidate);
char	**wildcard_values(const char *wildcard);
size_t	wildlen(const char *const *wildcard);
void	free_wildcard_values(char **wildcard_values);

#endif
