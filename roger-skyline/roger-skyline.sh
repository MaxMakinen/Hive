#!/bin/bash
# https://andreafortuna.org/2019/10/24/how-to-create-a-virtualbox-vm-from-command-line/

if [ $# == 1 ]; then
	MACHINENAME=$1
else
	MACHINENAME="roger-skyline-1"
fi

VBoxManage createvm --name $MACHINENAME --ostype "Debian_64" --register --basefolder 'pwd'

# Enable I/O APIC: Advanced Programmable Interrupt Controllers (APICs) are an x86 hardware feature that have replaced Programmable Interrupt Controllers (PICs). 
# With an I/O APIC, OSes can use more than 16 interrupt requests (IRQs) and therefore avoid IRQ sharing for improved reliability.
# Note: Enabling the I/O APIC is required, especially for 64-bit Windows guest OSes. It is also required if you want to use more than one virtual CPU in a virtual machine.
VBoxManage modifyvm $MACHINENAME --ioapic on
# --memory <memorysize>: Sets the amount of RAM, in MB, that the virtual machine should allocate for itself from the host.
# --vram <vramsize>: Sets the amount of RAM that the virtual graphics card should have.
VBoxManage modifyvm $MACHINENAME --memory 1024 --vram 128
VBoxManage modifyvm $MACHINENAME --nic1 nat
