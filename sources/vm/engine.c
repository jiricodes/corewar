/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 17:19:33 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			check_live_calls(t_vm *core)
{
	t_car		*tmp;
	ssize_t		limit;

	limit = CTD >= 0 ? core->cycle - CTD : core->cycle + CTD;
	limit = limit < 1 ? 1 : limit;
	limit = limit > core->cycle ? CTD : limit;
	tmp = core->car_list;
	vm_log(F_LOG, "[%zu]: Checking Lives:\n", core->cycle);
	while (tmp)
	{
		if (tmp->last_live < limit)
		{
			vm_log(F_LOG, "\n[%zu]: Carriage[%zu] failed to report live!\n",\
				core->cycle, tmp->id);
			log_carriage(tmp, F_LOG);
			core->car_list = delete_carriage(core->car_list, tmp->id);
			tmp = core->car_list;
			core->car_cnt--;
		}
		else
			tmp = tmp->next;
	}
	vm_log(F_LOG, "Total carriages alive [%zu]\n", core->car_cnt);
}

void			do_cycle(t_vm *core)
{
	t_car	*current;

	current = core->car_list;
	reset_car_cnt(core);
	while (current)
	{
		process_car(core, current);
		current = current->next;
	}
}

void			check_lives(t_vm *core)
{
	check_live_calls(core);
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
	log_arena(core->arena, core->flags->dump_size, F_LOG);
	log_vm_status(core, F_LOG);
}

void			engine(t_vm *core)
{
	core->checks = 0;
	core->cycle = 1;
	while (core->car_list && CTD >= 0)
	{
		if (core->cycle >= core->flags->dump_cycle)
		{
			do_dump(core);
			return ;
		}
		do_cycle(core);
		core->check_cd--;
		if (core->check_cd <= 0)
			check_lives(core);
		core->cycle++;
	}
	if (core->last_to_live)
		ft_printf("[%zu] Player (%d) %s won\n", core->cycle,\
			core->last_to_live->id, WINNER);
	else
		ft_printf("[%zu] Everyone is dead, total clusterfuck\n", core->cycle);
}
