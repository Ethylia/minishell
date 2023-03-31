/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:43:24 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 10:07:02 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <stddef.h>

size_t	count_wildcard_values(const char *wildcard);
int		matches_wildcard(const char *wildcard, const char *candidate);
char	**wildcard_values(const char *wildcard);
size_t	wildlen(const char *const *wildcard);
void	free_wildcard_values(char **wildcard_values);

#endif
