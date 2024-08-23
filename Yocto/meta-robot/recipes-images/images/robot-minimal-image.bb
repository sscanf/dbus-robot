inherit core-image

SUMMARY = "ZOKeypad Minimal Image"
DESCRIPTION = "Minimal image without graphical interface that just boots"

LICENSE = "MIT"
#IMAGE_FSTYPES = "squashfs"

#Prefix to the resulting deployable tarball name
export IMAGE_BASENAME = "zokeypad-minimal-image"
MACHINE_NAME ?= "${MACHINE}"
IMAGE_NAME = "${MACHINE_NAME}_${IMAGE_BASENAME}"

# Copy Licenses to image /usr/share/common-license
COPY_LIC_MANIFEST ?= "1"
COPY_LIC_DIRS ?= "1"

# Show Tezi EULA license
TEZI_SHOW_EULA_LICENSE ?= "1"

add_rootfs_version () {
    printf "${DISTRO_NAME} ${DISTRO_VERSION} (${DISTRO_CODENAME}) \\\n \\\l\n" > ${IMAGE_ROOTFS}/etc/issue
    printf "${DISTRO_NAME} ${DISTRO_VERSION} (${DISTRO_CODENAME}) %%h\n" > ${IMAGE_ROOTFS}/etc/issue.net
    printf "${IMAGE_NAME}\n\n" >> ${IMAGE_ROOTFS}/etc/issue
    printf "${IMAGE_NAME}\n\n" >> ${IMAGE_ROOTFS}/etc/issue.net
}
# add the rootfs version to the welcome banner
ROOTFS_POSTPROCESS_COMMAND += " add_rootfs_version;"

IMAGE_LINGUAS = "en-us"
#IMAGE_LINGUAS = "de-de fr-fr en-gb en-us pt-br es-es kn-in ml-in ta-in"

#CONMANPKGS ?= "connman connman-plugin-loopback connman-plugin-ethernet connman-plugin-wifi connman-client"
#${CONMANPKGS}

TASK_BASIC_SSHDAEMON = "openssh openssh-sftp openssh-sftp-server"

#packagegroup-tdx-graphical 

TORADEX_GROUP = " \
    packagegroup-boot \
    packagegroup-basic \
    packagegroup-base-tdx-cli \
    packagegroup-machine-tdx-cli \
    packagegroup-wifi-tdx-cli \
    packagegroup-wifi-fw-tdx-cli \
    packagegroup-tdx-cli \
    packagegroup-tdx-qt5 \
    udev-extraconf \
    ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'timestamp-service systemd-analyze', '', d)} \
"

IMAGE_INSTALL+= "${@bb.utils.contains("MACHINE", "qemux86-64", "","${TORADEX_GROUP}",d)} \
    packagegroup-basic \
"
                 
