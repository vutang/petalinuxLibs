#ifndef __PLIPCORE_LIB_H__
#define __PLIPCORE_LIB_H__

int rru_open_device();
int rru_close_device();

int rru_read_reg(int id, unsigned reg);
int rru_write_reg(int id, unsigned reg, unsigned value);

#endif
