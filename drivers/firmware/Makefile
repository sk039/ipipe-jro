#
# Makefile for the linux kernel.
#
obj-$(CONFIG_DMI)		+= dmi_scan.o
obj-$(CONFIG_DMI_SYSFS)		+= dmi-sysfs.o
obj-$(CONFIG_EDD)		+= edd.o
obj-$(CONFIG_EFI_PCDP)		+= pcdp.o
obj-$(CONFIG_DELL_RBU)          += dell_rbu.o
obj-$(CONFIG_DCDBAS)		+= dcdbas.o
obj-$(CONFIG_DMIID)		+= dmi-id.o
obj-$(CONFIG_ISCSI_IBFT_FIND)	+= iscsi_ibft_find.o
obj-$(CONFIG_ISCSI_IBFT)	+= iscsi_ibft.o
obj-$(CONFIG_FIRMWARE_MEMMAP)	+= memmap.o
obj-$(CONFIG_QCOM_SCM)		+= qcom_scm.o
ifdef CONFIG_64BIT
obj-$(CONFIG_QCOM_SCM)		+= qcom_scm-64.o
else
obj-$(CONFIG_QCOM_SCM)		+= qcom_scm-32.o
endif
CFLAGS_qcom_scm-32.o :=$(call as-instr,.arch_extension sec,-DREQUIRES_SEC=1)

obj-$(CONFIG_GOOGLE_FIRMWARE)	+= google/
obj-$(CONFIG_EFI)		+= efi/
obj-$(CONFIG_UEFI_CPER)		+= efi/
