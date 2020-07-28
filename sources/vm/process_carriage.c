/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_carriage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 06:21:47 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 06:27:40 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "oplist_cw.h"

static int		if_op(int8_t byte)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (byte == g_oplist[cnt].opcode)
			return (g_oplist[cnt].opcode - 1);
		cnt += 1;
	}
	return (-1);
}

static void		check_operation(t_vm *core, t_car *car)
{
	car->op_index = if_op(core->arena[car->pc]);
	if (car->op_index != -1)
	{
		car->cooldown = g_oplist[car->op_index].exec_cycles;
		ft_bzero(car->args, sizeof(t_args));
	}
	else
		car->step = 1;
}

void			process_car(t_vm *core, t_car *car)
{
	int	i;

	core->car_cnt++;
	if (car->pc >= MEM_SIZE || car->pc < 0)
		vm_log(1, "ERROR carriage[%zu] = [%zd]\n", car->id, car->pc);
	i = core->byte_owner[car->pc] - 1;
	if (i < core->n_players)
		core->champ[i]->car_cnt++;
	if (car->cooldown == 0 && car->op_index == -1)
		check_operation(core, car);
	if (car->cooldown != 0)
		car->cooldown--;
	if (car->cooldown == 0)
	{
		if (car->op_index != -1)
		{
			vm_log(F_LOG, "[%zu]: P%5zu | %s ", core->cycle,\
				car->id + 1, g_oplist[car->op_index].opname);
			g_oplist[car->op_index].op(core, car);
			vm_log(F_LOG, "\n");
			car->op_index = -1;
		}
		car->pc = (car->pc + car->step) % MEM_SIZE;
		car->pc = car->pc < 0 ? MEM_SIZE + car->pc : car->pc;
	}
}

void			reset_car_cnt(t_vm *core)
{
	int cnt;

	cnt = 0;
	core->car_cnt = 0;
	while (cnt < core->n_players)
	{
		core->champ[cnt]->car_cnt = 0;
		cnt++;
	}
}
