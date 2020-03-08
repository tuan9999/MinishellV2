/* ************************************************************************** */
/*                                                                            */
/*   File: parser.h                                       ::::::::            */
/*   Created on 2020/03/04 00:40:49                     :+:    :+:            */
/*   Created by dpattij <dpattij@student.codam.nl>     +:+                    */
/*                                                    +#+                     */
/*   void *data = NULL;                              +#+                      */
/*   while (data == NULL)                           #+#    #+#                */
/*       data = malloc(1337 * 42 * 21);            ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <ministd.h>
# include <vector.h>
# include <vm.h>

# define CMD_SEPERATOR ';'
# define STRING_SINGLE_QUOTE '\''
# define STRING_DOUBLE_QUOTE '"'
# define EOF -1

typedef struct	s_string_slice
{
	char		*str;
	size_t		len;
}				t_string_slice;

t_bool			seperate_commands(
				char *input,
				t_vector *commands);
int				evaluate_input(
				char *input,
				t_table *env);
t_bool			cb_command(
				char **input,
				t_command_pair *output);
t_bool			cb_operation(
				char **input,
				t_instruction *operation);
t_bool			cb_item(
				char **input,
				char **output);
t_bool			is_control(char c);
t_bool			is_not_control(char c);
t_bool			is_literal_space(char c);
t_bool			skip_atleast(
				char **input,
				char matcher,
				size_t times);
t_bool			take_number(
				char **input,
				size_t *out);
t_bool			take_while(
				char **input,
				char **output,
				t_bool (*matcher)(char));
t_bool			take_whilen(
				char **input,
				char **output,
				t_bool (*matcher)(char),
				size_t n);
t_bool			take_char(
				char **input,
				char *c);
t_bool			sanitize_line(
				char **input,
				char **out);
t_bool			parse_line(
				char **input,
				t_vector *instructions);

#endif
