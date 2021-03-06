/*
 * Machine description and loader.
 */

#ifndef __R5SIM_MACHINE__
#define __R5SIM_MACHINE__

#include <stdint.h>

#include <r5sim/list.h>

struct r5sim_core;

/*
 * Define a "machine". This is a single core - for now - and some memory.
 * Define several function pointers for accessing memory, device memory,
 * etc.
 */
struct r5sim_machine {
	struct {
		const char *name;
	} descr;

	struct r5sim_core *core;

	/*
	 * Base memory address and size; this is "DRAM".
	 */
	uint32_t    memory_base;
	uint32_t    memory_size;
	uint8_t    *memory;
	uint32_t   *memory_words;

	uint32_t    brom_base;
	uint32_t    brom_size;
	uint8_t    *brom;
	uint32_t   *brom_words;

	uint32_t    iomem_base;
	uint32_t    iomem_size;

	/*
	 * Load and store - will direct the loads and stores to either DRAM
	 * or the relevant IO device.
	 */
	uint32_t  (*memload32)(struct r5sim_machine *mach,
			       uint32_t paddr);
	uint16_t  (*memload16)(struct r5sim_machine *mach,
			       uint32_t paddr);
	uint8_t   (*memload8)(struct r5sim_machine *mach,
			      uint32_t paddr);
	void      (*memstore32)(struct r5sim_machine *mach,
				uint32_t paddr,
				uint32_t value);
	void      (*memstore16)(struct r5sim_machine *mach,
				uint32_t paddr,
				uint16_t value);
	void      (*memstore8)(struct r5sim_machine *mach,
			       uint32_t paddr,
			       uint8_t value);

	/*
	 * List of IO devices, e.g UARTs.
	 */
	struct list_head io_devs;
};

/*
 * Load the default machine; this is a machine that can be used if no
 * other machine is specified and loaded.
 *
 * TODO: Dynamic machine loading.
 */
struct r5sim_machine *
r5sim_machine_load_default(void);

/*
 * Load a bootrom image into the brom space in the machine. If this
 * fails it triggers an assert.
 */
void
r5sim_machine_load_brom(struct r5sim_machine *mach);

/*
 * Begin machine boot.
 */
void
r5sim_machine_boot(struct r5sim_machine *mach);

/*
 * Display the details for a machine.
 */
void
r5sim_machine_print(struct r5sim_machine *mach);

#endif
