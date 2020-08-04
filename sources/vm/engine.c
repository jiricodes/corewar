/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/04 18:40:01 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_car			*check_live_calls(t_vm *core, t_car *car, t_car **previous)
{
	ssize_t		diff;

	diff = core->cycle - car->last_live;
	if (diff >= core->cycles_to_die)
	{
		if (core->flags->log & LOG_DEATHS)
			ft_printf("[%zu]: Process %zu hasn't lived for %zd cycles (CTD %zd)\n",\
				core->cycle, car->id, diff, core->cycles_to_die);
		if (core->flags->log & LOG_DETAILS)
			log_carriage(car);
		if (*previous)
			(*previous)->next = car->next;
		else
			core->car_list = car->next;
		free(car->args);
		free(car);
		core->car_cnt--;
		return (*previous ? (*previous)->next : core->car_list);
	}
	*previous = car;
	return (car->next);
}

void			do_cycle(t_vm *core)
{
	t_car	*current;
	t_car	*previous;

	current = core->car_list;
	previous = NULL;
	reset_car_cnt(core);
	while (current)
	{
		process_car(core, current);
		if (core->check_cd <= 0)
			current = check_live_calls(core, current, &previous);
		else
		{
			previous = current;
			current = current->next;
		}
	}
	// current = core->car_list;
	// while (current)
	// {
	// 	ft_printf("Car%zu - ", current->id);
	// 	current = current->next;
	// }
	// ft_printf("\n");
}

void			check_lives(t_vm *core)
{
	core->checks++;
	if (core->live_cnt >= 21 || core->checks == MAX_CHECKS)
	{
		core->cycles_to_die -= CYCLE_DELTA;
		if (core->flags->log & LOG_CTD)
			ft_printf("[%zu] Cycle to die is now %zd\n",\
				core->cycle, core->cycles_to_die);
		core->checks = 0;
	}
	core->live_cnt = 0;
	core->check_cd = core->cycles_to_die;
}

static void		do_dump(t_vm *core)
{
	print_arena(core->arena, core->flags->dump_size);
	if (core->flags->log & LOG_DETAILS)
		log_vm_status(core);
}

void			engine(t_vm *core)
{
	core->checks = 0;
	core->cycle = 0;
	while (core->car_list && core->cycles_to_die >= 0)
	{
		if (core->check_cd <= 0)
			check_lives(core);
		core->cycle++;
		core->check_cd--;
		do_cycle(core);
		if (core->cycle >= core->flags->dump_cycle)
		{
			do_dump(core);
			return ;
		}
	}
	if (core->last_to_live)
		ft_printf("[%zu] Player (%d) %s won\n", core->cycle,\
			core->last_to_live->id, core->last_to_live->header->prog_name);
	else
		ft_printf("[%zu] Everyone is dead, total clusterfuck\n", core->cycle);
}
