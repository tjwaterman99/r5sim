/*
 * RISC-V core abstraction.
 */

#ifndef __R5SIM_CORE_H__
#define __R5SIM_CORE_H__

#include <stdint.h>

#include <r5sim/isa.h>

struct r5sim_machine;

struct r5sim_core {
	const char           *name;

	uint32_t              reg_file[32];
	uint32_t              pc;

	/*
	 * Machine this core belongs to; relevant for handling IO, DRAM
	 * access, etc.
	 */
	struct r5sim_machine *mach;

	/*
	 * Begin execution of this core at the specified start_addr.
	 */
	void (*exec)(struct r5sim_machine *mach,
		     struct r5sim_core *core,
		     uint32_t start_addr);
};

void
r5sim_core_describe(struct r5sim_core *core);

#endif
