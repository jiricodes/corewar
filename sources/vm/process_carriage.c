/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_carriage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 06:21:47 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/05 14:06:45 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "oplist_cw.h"

static int		if_op(int8_t byte, t_args *args)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (byte == g_oplist[cnt].opcode)
		{
			args->opcount = cnt;
			args->arg_cnt = g_oplist[cnt].arg_cnt;
			args->arg_code = g_oplist[cnt].arg_type_code;
			args->dir_size = g_oplist[cnt].t_dir_size;
			if (!args->arg_code)
			{
				args->arg_types[0] = g_oplist[cnt].arg_type[0];
				args->arg_types[1] = g_oplist[cnt].arg_type[1];
				args->arg_types[2] = g_oplist[cnt].arg_type[2];
			}
			return (g_oplist[cnt].opcode - 1);
		}
		cnt += 1;
	}
	return (-1);
}

static void		check_operation(t_vm *core, t_car *car)
{
	ft_bzero(car->args, sizeof(t_args));
	car->op_index = if_op(core->arena[car->pc], car->args);
	if (car->op_index != -1)
		car->cooldown = g_oplist[car->op_index].exec_cycles;
	else
		car->step = 1;
}

void			process_car(t_vm *core, t_car *car)
{
	int	i;
	ssize_t old;

	core->car_cnt++;
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
			g_oplist[car->op_index].op(core, car);
			car->op_index = -1;
		}
		old = car->pc;
		car->pc = (car->pc + car->step) % MEM_SIZE;
		car->pc = car->pc < 0 ? MEM_SIZE + car->pc : car->pc;
		if (core->flags->log & LOG_PC)
		{
			ft_printf(PC_STR, core->cycle, car->id, old, car->pc);
			if (core->cycle == 18109 && car->id == 926)
				log_car_in_arena(core->arena, 64, car->pc);
		}
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
