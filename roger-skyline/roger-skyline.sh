#!/bin/bash
# https://andreafortuna.org/2019/10/24/how-to-create-a-virtualbox-vm-from-command-line/
# https://www.virtualbox.org/manual/ch08.html#vboxmanage-modifyvm

if [ $# == 1 ]; then
	MACHINENAME=$1
else
	MACHINENAME="roger-skyline-1"
fi

PASSWORD="p4ssw0rd"
USER="user"
BASEFOLDER="/goinfre/mmakinen"
ISO="/Users/mmakinen/Downloads/debian-11.3.0-amd64-netinst.iso"

VBoxManage createvm --name $MACHINENAME --ostype "Debian_64" --register
# VBoxManage createvm --name $MACHINENAME --ostype "Debian_64" --register --basefolder $BASEFOLDER

VBoxManage modifyvm $MACHINENAME --ioapic on
# Enable I/O APIC: Advanced Programmable Interrupt Controllers (APICs) are an x86 hardware feature that have replaced Programmable Interrupt Controllers (PICs). 
# With an I/O APIC, OSes can use more than 16 interrupt requests (IRQs) and therefore avoid IRQ sharing for improved reliability.
# Note: Enabling the I/O APIC is required, especially for 64-bit Windows guest OSes. It is also required if you want to use more than one virtual CPU in a virtual machine.

VBoxManage modifyvm $MACHINENAME --rtcuseutc on
# --rtcuseutc on|off: Sets the real-time clock (RTC) to operate in UTC time. See Section 3.5.1, “Motherboard Tab”.

VBoxManage modifyvm $MACHINENAME  --mouse usbtablet
# --mouse <ps2|usb|usbtablet|usbmultitouch>: Specifies the mode of the mouse to be used in the VM. Available options are: ps2, usb, usbtablet, usbmultitouch.

# --memory <memorysize>: Sets the amount of RAM, in MB, that the virtual machine should allocate for itself from the host.
# --vram <vramsize>: Sets the amount of RAM that the virtual graphics card should have.

VBoxManage modifyvm $MACHINENAME --memory 1024 --vram 128 --cpus 2

VBoxManage modifyvm $MACHINENAME --nic1 bridged --bridgeadapter1 "en0: Ethernet"
# --nic<1-N> none|null|nat|natnetwork|bridged|intnet|hostonly|generic: Configures the type of networking for each of the VM's virtual network cards. Options are: not present (none), not connected to the host (null), use network address translation (nat), use the new network address translation engine (natnetwork), bridged networking (bridged), or use internal networking (intnet), host-only networking (hostonly), or access rarely used sub-modes (generic). These options correspond to the modes described in Section 6.2, “Introduction to Networking Modes”.
# Network Address Translation (NAT). If all you want is to browse the Web, download files, and view email inside the guest, then this default mode should be sufficient for you, and you can skip the rest of this section. Please note that there are certain limitations when using Windows file sharing. See Section 6.3.3, “NAT Limitations”

# This command creates a new virtual hard disk image. The syntax is as follows:
# 	VBoxManage createhd --filename <filename> --size <megabytes> [--format VDI|VMDK|VHD] (default: VDI) [--variant Standard,Fixed,Split2G,Stream,ESX]
# where the parameters mean:
#	--filename
# Allows to choose a file name. Mandatory.
#	--size
# Allows to define the image capacity, in 1 MiB units. Mandatory.
#	--format
# Allows to choose a file format for the output file different from the file format of the input file.
#	--variant
# Allows to choose a file format variant for the output file. It is a comma-separated list of variant flags. Not all combinations are supported, and specifying inconsistent flags will result in an error message.
# For compatibility with earlier versions of VirtualBox, the "createvdi" command is also supported and mapped internally to the "createhd" command.
#		VBoxManage createhd --filename $BASEFOLDER/[MACHINENAME]/[MACHINE NAME]_DISK.vdi --size 80000 --format VDI

# This command creates a new medium. The syntax is as follows:
# VBoxManage createmedium     [disk|dvd|floppy]    --filename <filename>
#                            [--size <megabytes>|--sizebyte <bytes>]
#                            [--diffparent <uuid>|<filename>
#                            [--format VDI|VMDK|VHD] (default: VDI)
#                            [--variant Standard,Fixed,Split2G,Stream,ESX]
# The parameters are as follows:
#	--filename <filename>
# Specifies a file name <filename> as an absolute path on the host file system. Mandatory.
#	--size <megabytes>
# Specifies the image capacity, in 1 MB units. Optional.
#	--diffparent <uuid>|<filename>
# Specifies the differencing image parent, either as a UUID or by the absolute pathname of the file on the host file system. Useful for sharing a base box disk image among several VMs.
#	--format VDI|VMDK|VHD
# Specifies the file format for the output file. Available options are VDI, VMDK, VHD. The default format is VDI. Optional.
#	--variant
# Specifies any required file format variants for the output file. This is a comma-separated list of variant flags. Options are Standard,Fixed,Split2G,Stream,ESX. Not all combinations are supported, and specifying mutually incompatible flags results in an error message. Optional.

#	VBoxManage createmedium --filename $BASEFOLDER/$MACHINENAME/${MACHINENAME}_DISK.vdi --size 8000 --format VDI
# -- size 8000 ends u with 7.8GB disc inside the VM

VBoxManage createmedium --filename $BASEFOLDER/$MACHINENAME/${MACHINENAME}_DISK.vdi --sizebyte 8000000000 --format VDI

#	https://www.virtualbox.org/manual/ch08.html#vboxmanage-storagectl
VBoxManage storagectl $MACHINENAME --name "SATA Controller" --add sata --controller IntelAhci
#	https://www.virtualbox.org/manual/ch08.html#vboxmanage-storageattach
VBoxManage storageattach $MACHINENAME --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium  $BASEFOLDER/$MACHINENAME/${MACHINENAME}_DISK.vdi
VBoxManage storagectl $MACHINENAME --name "IDE Controller" --add ide --controller PIIX4
VBoxManage storageattach $MACHINENAME --storagectl "IDE Controller" --port 1 --device 0 --type dvddrive --medium $ISO
VBoxManage modifyvm $MACHINENAME --boot1 dvd --boot2 disk --boot3 none --boot4 none

VBoxManage unattended install $MACHINENAME --user=$USER --password=$PASSWORD --locale=en_UK --time-zone=UTC --iso=$ISO

VBoxManage startvm $MACHINENAME --type headless


#	chipset PIIX3
#	I/O APIC Enabled
#	hardware clock in UTC time
#	2-3 cores
#	https://docs.oracle.com/en/virtualization/virtualbox/6.0/user/vboxmanage-list.html
#	https://www.openlogic.com/blog/how-use-vagrant-and-virtualbox
