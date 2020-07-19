# This is an automatically generated makefile.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

# QNX Internal Start
DEFCOMPILER_TYPE_x86=gcc
GCC_VERSION_x86=4.8.3
DEFCOMPILER_TYPE_arm=gcc
GCC_VERSION_arm=4.8.3
DEFCOMPILER_TYPE_sh=gcc
GCC_VERSION_sh=4.8.3
DEFCOMPILER_TYPE_ppc=gcc
GCC_VERSION_ppc=4.8.3
DEFCOMPILER_TYPE_mips=gcc
GCC_VERSION_mips=4.8.3
DEFCOMPILER_TYPE_aarch64=gcc
GCC_VERSION_aarch64=4.8.3
DEFCOMPILER_TYPE_x86_64=gcc
GCC_VERSION_x86_64=4.8.3

CCFLAGS+=-O1
LDFLAGS+=-lang-c++
EXTRA_SUFFIXES+=cxx cpp
EXTRA_CLEAN+=*.ii

VFLAG_g+=-gstabs+

include $(MKFILES_ROOT)/qmacros.mk


ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

# QNX Internal End

include $(MKFILES_ROOT)/qtargets.mk
OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))
