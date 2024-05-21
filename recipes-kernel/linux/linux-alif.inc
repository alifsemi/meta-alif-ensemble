# Copyright (C) 2024 Alif Semiconductor - All Rights Reserved.
# Use, distribution and modification of this code is permitted under the
# terms stated in the Alif Semiconductor Software License Agreement
#
# You should have received a copy of the Alif Semiconductor Software
# License Agreement with this file. If not, please write to:
# contact@alifsemi.com, or visit: https://alifsemi.com/license

SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-graphics", "file://graphics.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-nfs", "file://nfs.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-sd-share", "file://sd.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-sd-boot", "file://sd_boot.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-hwsem", "file://hwsem.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-mhu", "file://mhuv2.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-usb", "file://usb.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-spi", "file://spi.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-ethernet", "file://ethernet.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-usb-host", "file://usb_host.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-cdc200", "file://cdc200.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-i2c-i3c", "file://i2c-i3c.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-i2s", "file://i2s.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-utimer", "file://utimer.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-i3c", "file://i3c.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-crc", "file://crc.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-pdm", "file://pdm.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-i2c", "file://i2c.cfg", "" ,d)}"
SRC_URI_append += " ${@bb.utils.contains("DISTRO_FEATURES", "apss-mipicsi", "file://mipicsi.cfg", "" ,d)}"

PR .= ".12"
inherit dct-kernel

KERNEL_CC_append = " -DA32_HWSEM_MST_ID=${A32_HWSEM_MST_ID} "

do_compile_prepend () {
    if [ -e "${B}/.config" ]; then
        sed -i "s:^CONFIG_XIP_PHYS_ADDR=.*:CONFIG_XIP_PHYS_ADDR=${XIP_KERNEL_LOAD_ADDR}:g" ${B}/.config
        sed -i "s:^CONFIG_MTD_PHYSMAP_START=.*:CONFIG_MTD_PHYSMAP_START=${KERNEL_MTD_START_ADDR}:g" ${B}/.config
        sed -i "s:^CONFIG_MTD_PHYSMAP_LEN=.*:CONFIG_MTD_PHYSMAP_LEN=${KERNEL_MTD_LEN}:g" ${B}/.config
        sed -i "s:^CONFIG_PHYS_OFFSET=.*:CONFIG_PHYS_OFFSET=${KERNEL_XIP_RAM}:g" ${B}/.config
    fi
}


do_aes_enc() {
 if [ "${AES_EN}" = "1" ] ; then
    for iter in ${KERNEL_IMAGETYPES} ; do
        if [ "$iter" = "xipImage" ] ; then
            ${STAGING_BINDIR_NATIVE}/python3-native/python3 ${ALIFBASE}/lib/CSPI_AES128_ECB.py -i ${B}/${KERNEL_OUTPUT_DIR}/$iter -o ${B}/${KERNEL_OUTPUT_DIR}/$iter.enc -k ${AES_ENC_KEY} -d 1
            mv ${B}/${KERNEL_OUTPUT_DIR}/$iter ${B}/${KERNEL_OUTPUT_DIR}/$iter.orig
            mv ${B}/${KERNEL_OUTPUT_DIR}/$iter.enc ${B}/${KERNEL_OUTPUT_DIR}/$iter
        fi
    done
 fi
}

addtask aes_enc before do_install after do_compile

python __anonymous () {
    machine = d.getVar('MACHINE')
    smp = d.getVar('SMP')

    if machine == 'devkit-e5' and smp == '1':
        bb.fatal("Machine %s does not support SMP. Try building images without SMP (SMP = '0')" %(machine));
}
