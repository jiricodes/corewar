/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op10_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 07:23:20 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_ldi(t_vm *core, t_car *car, int val[3])
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d %d r%d\n", core->cycle,\
			car->id, "ldi", val[0], val[1], val[2]);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d %d r%d\n", core->cycle,\
			car->id, "ldi", val[0], val[1], val[2]);
		vfx_write_log(core, tmp, car->pc);
		free(tmp);
	}
}

static void	do_ldi(t_vm *core, t_args *args, t_car *car)
{
	int		val[3];

	if (args->arg_types[0] == T_IND)
		val[0] = read_arena(core->arena, car->pc,\
			args->arg[0] % IDX_MOD, REG_SIZE);
	else if (args->arg_types[0] == T_DIR)
		val[0] = args->arg[0];
	else if (args->arg_types[0] == T_REG)
		val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_REG)
		val[1] = car->reg[args->arg[1] - 1];
	else if (args->arg_types[1] == T_DIR)
		val[1] = args->arg[1];
	val[2] = args->arg[2];
	car->reg[val[2] - 1] = read_arena(core->arena, car->pc, \
							(val[0] + val[1]) % IDX_MOD, REG_SIZE);
	if (core->flags->log & LOG_OPS)
		log_ldi(core, car, val);
}

void		op_ldi(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_ldi(core, car->args, car);
	}
	get_step(car, car->args);
}
