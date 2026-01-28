# Copyright (C) 2024 Alif Semiconductor - All Rights Reserved.
# Use, distribution and modification of this code is permitted under the
# terms stated in the Alif Semiconductor Software License Agreement
#
# You should have received a copy of the Alif Semiconductor Software
# License Agreement with this file. If not, please write to:
# contact@alifsemi.com, or visit: https://alifsemi.com/license

ISSI_FLASH_EN ?= "${@'1' if d.getVar('MACHINE').startswith('devkit-e') else '0'}"
MX_FLASH_EN ?= "${@'1' if d.getVar('MACHINE').startswith('appkit-e') else '0'}"
KERNEL_MTD_START_ADDR ?= "0xC0000000"
KERNEL_MTD_LEN ?= "0x400000"
XIP_KERNEL_LOAD_ADDR ?= "0xC0800000"
