/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenvalidation3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:52 by francoma          #+#    #+#             */
/*   Updated: 2023/03/29 16:13:06 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "tokenvalidation.h"
#include "util/util.h"
#include "data.h"
#include "env.h"

static void	print_token_error(t_token *t)
{
	if (!t)
		return ;
	while (t->type == tws)
		t++;
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (!t->type)
		write(2, "newline", 7);
	else
		write(2, t->val, t->len);
	write(2, "'\n", 2);
}

static t_token	*find_token_error(t_token *tokens)
{
	size_t	i;

	if (!all_parenthesis_closed(tokens))
		return (tokens + count_tokens(tokens));
	i = skip_ws_pin(tokens);
	if (!is_word(tokens + i) && !is_redir(tokens + i))
		return (tokens + i);
	while (tokens[i].type)
	{
		if (tokens[i].type & (tpipe | tor | tand | tpin)
			&& !next_to_word(tokens + i) && !next_to_redir(tokens + i)
			&& !next_to(tokens + i, tpin))
			return (tokens + i + 1);
		else if (is_redir(tokens + i) && !next_to_word(tokens + i))
			return (tokens + i + 1);
		else if (tokens[i].type == tpout
			&& (next_to_word(tokens + i) || next_to(tokens + i, tpin)))
			return (tokens + i + 1);
		else if (is_word(tokens + i) && next_to(tokens + i, tpin))
			return (tokens + i + 1);
		i++;
	}
	return (NULL);
}

int	token_error(t_token *tokens)
{
	t_token	*t;
	char	*stat;

	t = find_token_error(tokens);
	if (t)
	{
		print_token_error(t);
		update_env(&(getdata()->local_env), "?=258");
		return (1);
	}
	return (0);
}

// #include <stdio.h>
// void	test(char *line, int success)
// {
// 	if (token_error(tokenize(line)) == success)
// 		printf("Error: %s\n", line);
// }

// int main()
// {
// 	test("|| echo", 1);
// 	test("a|| >", 1);
// 	test("a|| >          e", 0);
// 	test("a||>e", 0);
// 	test("(e)", 0);
// 	test("((e)", 1);
// 	test("( ( ( )   (e)            ))", 1);
// 	test("( ( (   (e)            )))", 0);
// 	test("( ( (   (e)      |      )))", 1);
// 	// mot suivi de (
// 	test("echo (ok)", 1);
// 	test("echo ok (> o)", 1);
// 	// ) suivi de mot ou (
// 	test("(echo) ok > o", 1);
// 	test("(e)(a)", 1);
// 	test("echo ok > (o)", 1);
// 	test("(echo ok) > o", 0);
// 	test("(<o cat)", 0);
// 	test("e && ((e))", 0);
// 	test("e && (e)", 0);
// 	test("(e &&) (e)", 1);
// }
