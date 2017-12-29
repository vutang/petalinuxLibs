#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include "libplIpcore.h"
#include "plIpcore_def.h"

#define DEV_NAME "/dev/plIpcore"

static int device_fd = -1;
static int rru_send_ioctl(unsigned long cmd, unsigned long arg);

int rru_open_device(){
    
    if (device_fd == -1){
        device_fd = open(DEV_NAME, O_WRONLY);
    }
    
    return device_fd > 0? 0 : -1;
}

int rru_close_device(){
    if (device_fd > 0){
        close(device_fd);
    }
    device_fd = -1;

    return 0;
}

int rru_read_reg(int id, unsigned reg){
     // printf("Read: id = %d, reg = %x\n", id, reg);
    int ret;
    plip_iocReg_t iocReg;

    iocReg.id = id;
    iocReg.addr =  reg;
    ret = rru_send_ioctl(RRU_IOC_REG_READ, &iocReg );

    return ret < 0? ret: iocReg.value;
}

int rru_write_reg(int id, unsigned reg, unsigned value){
    // printf("Write: id = %d, reg = %x, value = %x\n", id, reg, value);
    int ret;
    plip_iocReg_t iocReg;

    iocReg.id = id;
    iocReg.addr=  reg;
    iocReg.value = value;
    
    ret = rru_send_ioctl(RRU_IOC_REG_WRITE, &iocReg);

    return  ret;
}

static int rru_send_ioctl(unsigned long cmd, unsigned long arg){
    int ret;

    if (device_fd <  0){
        printf("Device not yet opened\n");
        return -1;
    }

    ret = ioctl(device_fd, cmd, arg);

    return ret;
}