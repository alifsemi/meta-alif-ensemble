FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += "\
    file://0001-rkisp1-support-multiple-bridge-subdevices.patch \
    file://0002-device-enumerator-sysfs-find-media-nodes-without-udev.patch \
    file://0003-ipa-add-arx3a0-analogue-gain-helper.patch \
    file://0004-ipa-rkisp1-accept-isp8000pico-revision.patch \
    file://0005-ipa-rkisp1-arx3a0-cpi-exposure.patch \
    file://0006-ipa-rkisp1-cap-arx3a0-exposure-at-cpi-init.patch \
"

# Iota uses busybox-mdev. libudev enumerate only returns devices that
# udevd has marked initialized, so cam would never see /dev/media0.
EXTRA_OEMESON += "-Dudev=disabled"

# The recipe default is "auto", which also builds every pipeline whose
# dependencies happen to be present. A plain assignment is required:
# the recipe already set this with ??=, so ??= here would not replace it.
LIBCAMERA_PIPELINES = "rkisp1"
