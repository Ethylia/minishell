/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenvalidation1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:16:08 by francoma          #+#    #+#             */
/*   Updated: 2023/03/28 14:13:22 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "token.h"
#include "tokenvalidation.h"

static size_t	skip_ws_pin(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i].type == tws || tokens[i].type == tpin)
		i++;
	return (i);
}

static int	all_parenthesis_closed(t_token *t)
{
	size_t	in_count;
	size_t	out_count;

	in_count = 0;
	out_count = 0;
	while (t->type)
	{
		if (t->type == tpin && !t->quote)
			in_count++;
		else if (t->type == tpout && !t->quote)
			out_count++;
		t++;
	}
	return (in_count == out_count);
}

static size_t	count_tokens(t_token *t)
{
	size_t	i;

	i = 0;
	while (t[i].type)
		i++;
	return (i);
}

void	print_unexpected_token(t_token *t)
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

t_token	*unexpected_token(t_token *tokens)
{
	size_t	i;

	if (!all_parenthesis_closed(tokens))
		return (tokens + count_tokens(tokens));
	i = skip_ws_pin(tokens);
	if (!is_word(tokens + i) && !is_redir(tokens + i))
		return (tokens + i);
	while (tokens[i].type)
	{
		if ((tokens[i].type == tpipe || tokens[i].type == tor
				|| tokens[i].type == tand || tokens[i].type == tpin)
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

// #include <stdio.h>
// void	test(char *line, int expected)
// {
// 	t_token	*bad_token;

// 	bad_token = unexpected_token(tokenize(line));
// 	if (bad_token)
// 		print_unexpected_token(bad_token);
// 	if ((int) !!bad_token == expected)
// 		printf("Error: %s\n", line);
// }

// int main()
// {
// 	test("|| echo", 0);
// 	test("a|| >", 0);
// 	test("a|| >          e", 1);
// 	test("a||>e", 1);
// 	test("(e)", 1);
// 	test("((e)", 0);
// 	test("( ( ( )   (e)            ))", 0);
// 	test("( ( (   (e)            )))", 1);
// 	test("( ( (   (e)      |      )))", 0);
// 	// mot suivi de (
// 	test("echo (ok)", 0);
// 	test("echo ok (> o)", 0);
// 	// ) suivi de mot ou (
// 	test("(echo) ok > o", 0);
// 	test("(e)(a)", 0);
// 	test("echo ok > (o)", 0);
// 	test("(echo ok) > o", 1);
// 	test("(<o cat)", 1);
// 	test("e && ((e))", 1);
// 	test("e && (e)", 1);
// 	test("(e &&) (e)", 0);
// }
