/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op14.lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/06 19:33:31 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_lldi(t_vm *core, size_t car_id, int val[3])
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d %d r%d\n", core->cycle,\
			car_id, "lldi", val[0], val[1], val[2]);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d %d r%d\n", core->cycle,\
			car_id, "lldi", val[0], val[1], val[2]);
		vfx_write_log(core, tmp);
		free(tmp);
	}
}

static void	do_lldi(t_vm *core, t_args *args, t_car *car)
{
	int	val[3];

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
	car->reg[val[2] - 1] = read_arena(core->arena, car->pc,\
		val[0] + val[1], REG_SIZE);
	car->carry = (car->reg[val[2] - 1]) ? 0 : 1;
	if (core->flags->log & LOG_OPS)
		log_lldi(core, car->id, val);
}

void		op_lldi(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_lldi(core, car->args, car);
	}
	get_step(car, car->args);
}
