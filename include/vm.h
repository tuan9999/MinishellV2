/* ************************************************************************** */
/*                                                                            */
/*   File: vm.h                                           ::::::::            */
/*   Created on 2020/03/04 01:32:22                     :+:    :+:            */
/*   Created by dpattij <dpattij@student.codam.nl>     +:+                    */
/*                                                    +#+                     */
/*   void *data = NULL;                              +#+                      */
/*   while (data == NULL)                           #+#    #+#                */
/*       data = malloc(1337 * 42 * 21);            ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <table.h>

typedef enum	e_opcode
{
	OP_COMMAND,
	OP_CALL,
	OP_PIPE,
	OP_WRITE,
	OP_READ,
	OP_APPEND,
	OP_NOP
}				t_opcode;

/*
** The args vector in s_command_pair is of type t_vector<char *>
*/

typedef struct	s_command_pair
{
	char		*command;
	t_vector	args;
}				t_command_pair;

typedef union	u_operand
{
	t_command_pair	pair;
	char			*filename;
}				t_operand;

typedef struct	s_instruction
{
	t_opcode		opcode;
	t_operand		operand;
}				t_instruction;

typedef struct	s_vm_state
{
	t_vector	callstack;
	t_vector	pipestack;
	t_table		*env;
}				t_vm_state;

typedef struct	s_dispatch_item
{
	t_opcode	opcode;
	int			(*fn)(t_instruction *, t_vm_state *);
}				t_dispatch_item;

int				vm_execute(
				t_vector *instructions,
				t_table *env);
int				run_process(
				t_vector *args,
				t_vector *pipe_stack,
				const int pipes[2],
				t_table *env);
int				handle_op_append(
				t_instruction *instruction,
				t_vm_state *state);
int				handle_op_command(
				t_instruction *instruction,
				t_vm_state *state);
int				handle_op_call(
				t_instruction *instruction,
				t_vm_state *state);
int				handle_op_pipe(
				t_instruction *instruction,
				t_vm_state *state);
int				handle_op_read(
				t_instruction *instruction,
				t_vm_state *state);
int				handle_op_write(
				t_instruction *instruction,
				t_vm_state *state);

#endif
