/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:43:24 by francoma          #+#    #+#             */
/*   Updated: 2023/03/17 16:05:47 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

int		matches_wildcard(const char *wildcard, const char *candidate);
char	**wildcard_values(const char *wildcard);

#endif
