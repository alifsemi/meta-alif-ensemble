SUMMARY = "Trusted Firmware for Cortex-A"
DESCRIPTION = "Trusted Firmware-A"
HOMEPAGE = "https://github.com/ARM-software/arm-trusted-firmware"
LICENSE = "BSD-3-Clause & Alif"
LIC_FILES_CHKSUM = "file://license.rst;md5=c709b197e22b81ede21109dbffd5f363"
DEPENDS += " dtc-native coreutils-native"
DEPENDS += " ${TF-A_DEPENDS} "
PR = "r28"

SRC_URI = "${TFA_TREE};branch=${TFA_BRANCH}"
SRCREV = "${AUTOREV}"

TF-A_DEPENDS ?= ""
S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

LDFLAGS[unexport] = "1"

TF-A_PLATFORM ?= "fvp"
TF-A_ARCH ?= "aarch32"
TF-A_DEBUG ?= "1"
TF-A_AARCH32_SP ?= "sp_min"
TF-A_BL33 ?= ""

TF-A_TARGET_IMAGES ?= "bl32"
TF-A_EXTRA_OPTIONS ?= ""

inherit deploy

do_compile() {
    rm -rf ${B}
    mkdir -p ${B}

    oe_runmake -C ${S} BUILD_BASE=${B} \
      BUILD_PLAT=${B}/${TF-A_PLATFORM}/ \
      PLAT=${TF-A_PLATFORM} \
      DEBUG=${TF-A_DEBUG} \
      ARCH=${TF-A_ARCH} \
      CROSS_COMPILE=${TARGET_PREFIX} \
      AARCH32_SP=${TF-A_AARCH32_SP} \
      BL33=${TF-A_BL33} \
      ${TF-A_EXTRA_OPTIONS} \
      ${TF-A_TARGET_IMAGES}
}


do_install() {
        [ -f ${B}/${TF-A_PLATFORM}/bl32.bin ] && cp -f ${B}/${TF-A_PLATFORM}/bl32.bin ${D}/bl32.bin
}

do_deploy() {
       [ -f ${D}/bl32.bin ] && install -D -p -m 0644 ${D}/bl32.bin ${DEPLOYDIR}/bl32.bin
}

addtask deploy before do_build after do_install

FILES_${PN} = "/bl32.bin"

python __anonymous () {
    machine = d.getVar('MACHINE')
    smp = d.getVar('SMP')

    if machine == 'devkit-e5' and smp == '1':
        bb.fatal("Machine %s does not support SMP. Try building images without SMP (SMP = '0')" %(machine));
}
