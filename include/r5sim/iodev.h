/*
 * An IO device model.
 */

#ifndef __R5SIM_IODEV_H__
#define __R5SIM_IODEV_H__

#include <stdint.h>

#include <r5sim/list.h>

struct r5sim_machine;

struct r5sim_iodev {
	const char           *name;

	/*
	 * Pointer back to the machine for doing "DMA".
	 */
	struct r5sim_machine *mach;

	/*
	 * Base IO address offset. This is offset from machine.iomem_base.
	 */
	uint32_t              io_offset;
	uint32_t              io_size;

	/*
	 * IO accessor functions; these are 0 based from io_offset.
	 */
	uint32_t            (*readl)(struct r5sim_iodev *dev,
				     uint32_t offs);
	void                (*writel)(struct r5sim_iodev *dev,
				      uint32_t offs, uint32_t val);

	/*
	 * List entry for when this device is attached to a machine.
	 */
	struct list_head      mach_node;

	/*
	 * Private data for implementing the device.
	 */
	void                 *priv;
};

void
r5sim_iodev_describe(struct r5sim_iodev *dev);

#endif
