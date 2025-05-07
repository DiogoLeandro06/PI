obj-m += hello.o


ARCH_USED := riscv
COMPILER_PATH := riscv64-linux-gnu- 


PWD := $(shell pwd) 
KERNELPATH := ../../../../duo-buildroot-sdk/linux_5.10 # Add path to linux directory from repository: https://github.com/milkv-duo/duo-buildroot-sdk/

all:
	make ARCH=$(ARCH_USED) CROSS_COMPILE=$(COMPILER_PATH) -C $(KERNELPATH) M=$(PWD) modules

clean:
	make -C $(KERNELPATH) M=$(PWD) clean
