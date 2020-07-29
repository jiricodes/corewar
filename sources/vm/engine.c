/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/29 17:43:41 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_car			*check_live_calls(t_vm *core, t_car *car)
{
	ssize_t		limit;
	t_car		*next;

	limit = core->cycles_to_die >= 0 ? core->cycle - core->cycles_to_die : core->cycle + core->cycles_to_die;
	limit = limit < 1 ? 1 : limit;
	limit = limit > (ssize_t)core->cycle ? core->cycles_to_die : limit;
	vm_log(core->flags->log, "\n[%zu]: Carriage[%zu] live [%zu] limit [%zd]\n",\
			core->cycle, car->id, car->last_live, limit);
	if ((ssize_t)car->last_live < limit)
	{
		vm_log(core->flags->log, "\n[%zu]: Carriage[%zu] failed to report live!\n",\
			core->cycle, car->id);
		log_carriage(car, core->flags->log);
		next = car->next;
		core->car_list = delete_carriage(core->car_list, car->id);
		core->car_cnt--;
		return (next);
	}
	return (car->next);
}

void			do_cycle(t_vm *core)
{
	t_car	*current;

	current = core->car_list;
	reset_car_cnt(core);
	while (current)
	{
		process_car(core, current);
		if (core->check_cd <= 0)
			current = check_live_calls(core, current);
		else
			current = current->next;
	}
}

void			check_lives(t_vm *core)
{
	if (core->live_cnt >= 21 || core->checks == MAX_CHECKS)
	{
		core->cycles_to_die -= CYCLE_DELTA;
		core->checks = 0;
	}
	core->live_cnt = 0;
	core->check_cd = core->cycles_to_die;
	core->checks++;
}

static void		do_dump(t_vm *core)
{
	print_arena(core->arena, core->flags->dump_size);
	log_arena(core->arena, core->flags->dump_size, core->flags->log);
	log_vm_status(core, core->flags->log);
}

void			engine(t_vm *core)
{
	core->checks = 0;
	core->cycle = 1;
	while (core->car_list && core->cycles_to_die >= 0)
	{
		if (core->cycle >= core->flags->dump_cycle)
		{
			do_dump(core);
			return ;
		}
		core->check_cd--;
		do_cycle(core);
		if (core->check_cd <= 0)
			check_lives(core);
		core->cycle++;
	}
	if (core->last_to_live)
		ft_printf("[%zu] Player (%d) %s won\n", core->cycle,\
			core->last_to_live->id, core->last_to_live->header->prog_name);
	else
		ft_printf("[%zu] Everyone is dead, total clusterfuck\n", core->cycle);
}
