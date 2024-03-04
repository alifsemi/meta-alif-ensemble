# Copyright (C) 2022 Alif Semiconductor - All Rights Reserved.
# Use, distribution and modification of this code is permitted under the
# terms stated in the Alif Semiconductor Software License Agreement
#
# You should have received a copy of the Alif Semiconductor Software
# License Agreement with this file. If not, please write to:
# contact@alifsemi.com, or visit: https://alifsemi.com/license

PR = "r1"

require recipes-kernel/linux/linux-yocto.inc
require recipes-kernel/linux/linux-alif.inc

SRC_URI = "${ALIF_KERNEL_TREE};branch=${ALIF_KERNEL_BRANCH}"

KCONFIG_MODE="--allnoconfig"
SRCREV ??= "${ALIF_KERNEL_BRANCH}"

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

KERNEL_VERSION_SANITY_SKIP = "1"
BB_GENERATE_MIRROR_TARBALLS = "0"

LINUX_VERSION ?= "5.4.25"

PV = "${LINUX_VERSION}+git${SRCPV}"

S = "${WORKDIR}/git"

#do_kernel_configme() {
#}

COMPATIBLE_MACHINE = "(devkit-e).*|(appkit-e).*"
