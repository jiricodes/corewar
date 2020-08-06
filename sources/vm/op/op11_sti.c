/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op11_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/06 19:00:57 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

// inline void	log_sti(t_vm *core, size_t car_id, int val)
// {
// 	if (!core->flags->vfx)
		
// 	else
// 	{
// 		tmp = ft_strnew(LOG_BUF);
// 		ft_sprintf(tmp, 
// 		vfx_write_log(core, tmp);
// 		free(tmp);
// 	}
// }

static void	do_sti(t_vm *core, t_args *args, t_car *car)
{
	int32_t	val[3];

	val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_IND)
		val[1] = read_arena(core->arena, car->pc,\
			args->arg[1] % IDX_MOD, REG_SIZE);
	else if (args->arg_types[1] == T_DIR)
		val[1] = args->arg[1];
	else if (args->arg_types[1] == T_REG)
		val[1] = car->reg[args->arg[1] - 1];
	if (args->arg_types[2] == T_REG)
		val[2] = car->reg[args->arg[2] - 1];
	else if (args->arg_types[2] == T_DIR)
		val[2] = args->arg[2];
	write_bytes(car->pc + (val[1] + val[2]) % IDX_MOD, val[0], car, core);
	if (core->flags->log & LOG_OPS)
	{
		ft_printf("[%zu]\tP %4zu | %s ", core->cycle, car->id, "sti");
		ft_printf("r%d %d %d\n", args->arg[0], val[1], val[2]);
	}
}

void		op_sti(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_sti(core, car->args, car);
	}
	get_step(car, car->args);
}
