#!/bin/bash
# https://andreafortuna.org/2019/10/24/how-to-create-a-virtualbox-vm-from-command-line/
# https://www.virtualbox.org/manual/ch08.html#vboxmanage-modifyvm
# https://www.edwardstafford.com/how-to-using-vboxmanage-to-delete-a-virtual-machine-from-virtualbox/
# Delete VM: 
# Step one: Get the name or UUID and details of your VM
#  VBoxManage list vms
# Step two: Get the disc information for your VM
#  VBoxManage showvminfo <Virtual Machine Name or UUID>
# Step Three: Disassociate the Virtual Disk[s]
#  VBoxManage modifyvm VNAS –hda none
# Step Four: Unregister and delete the VM
#  VBoxManage unregistervm <Virtual Machine Name or UUID>Â –delete
#  VBoxManage unregistervm VNAS –delete
# Step Five: Confirm
#  VBoxManage list vms

if [ $# == 1 ]; then
	VM=$1
else
	VM="roger-skyline"
fi

PASSWORD="p4ssw0rd"
USER="user"
BASEFOLDER="/goinfre/mmakinen"
ISO="/Users/mmakinen/Downloads/debian-11.6.0-amd64-netinst.iso"

VBoxManage createvm --name $VM --ostype "Debian_64" --register
# VBoxManage createvm --name $VM --ostype "Debian_64" --register --basefolder $BASEFOLDER

VBoxManage modifyvm $VM --ioapic on
# Enable I/O APIC: Advanced Programmable Interrupt Controllers (APICs) are an x86 hardware feature that have replaced Programmable Interrupt Controllers (PICs). 
# With an I/O APIC, OSes can use more than 16 interrupt requests (IRQs) and therefore avoid IRQ sharing for improved reliability.
# Note: Enabling the I/O APIC is required, especially for 64-bit Windows guest OSes. It is also required if you want to use more than one virtual CPU in a virtual machine.

#VBoxManage modifyvm $VM --rtcuseutc on
# --rtcuseutc on|off: Sets the real-time clock (RTC) to operate in UTC time. See Section 3.5.1, “Motherboard Tab”.

VBoxManage modifyvm $VM  --mouse usbtablet
# --mouse <ps2|usb|usbtablet|usbmultitouch>: Specifies the mode of the mouse to be used in the VM. Available options are: ps2, usb, usbtablet, usbmultitouch.

# --memory <memorysize>: Sets the amount of RAM, in MB, that the virtual machine should allocate for itself from the host.
# --vram <vramsize>: Sets the amount of RAM that the virtual graphics card should have.

VBoxManage modifyvm $VM --memory 2048 --vram 128 --cpus 2

# VBoxManage modifyvm $VM --nic1 nat
# VBoxManage modifyvm $VM --natpf1 "ssh,tcp,,2222,,22"
# https://www.virtualbox.org/manual/ch06.html#network_nat

VBoxManage modifyvm $VM --nic1 bridged --bridgeadapter1 "en0: Ethernet"
# --nic<1-N> none|null|nat|natnetwork|bridged|intnet|hostonly|generic: Configures the type of networking for each of the VM's virtual network cards. Options are: not present (none),
# not connected to the host (null), use network address translation (nat), use the new network address translation engine (natnetwork), bridged networking (bridged), or use internal networking (intnet),
# host-only networking (hostonly), or access rarely used sub-modes (generic). These options correspond to the modes described in Section 6.2, “Introduction to Networking Modes”.
# With bridged networking, Oracle VM VirtualBox uses a device driver on your host system that filters data from your physical network adapter. This driver is therefore called a net filter driver.
# This enables Oracle VM VirtualBox to intercept data from the physical network and inject data into it, effectively creating a new network interface in software. When a guest is using such a new software interface,
# it looks to the host system as though the guest were physically connected to the interface using a network cable. The host can send data to the guest through that interface and receive data from it.
# This means that you can set up routing or bridging between the guest and the rest of your network.

#	Note
#	Even though TAP interfaces are no longer necessary on Linux for bridged networking, you can still use TAP interfaces for certain advanced setups, since you can connect a VM to any host interface.
#
# To enable bridged networking, open the Settings dialog of a virtual machine, go to the Network page and select Bridged Network in the drop-down list for the Attached To field. 
# Select a host interface from the list at the bottom of the page, which contains the physical network interfaces of your systems.
# On a typical MacBook, for example, this will allow you to select between en1: AirPort, which is the wireless interface, and en0: Ethernet, which represents the interface with a network cable.

#	Note
#	Bridging to a wireless interface is done differently from bridging to a wired interface, because most wireless adapters do not support promiscuous mode.
# All traffic has to use the MAC address of the host's wireless adapter, and therefore Oracle VM VirtualBox needs to replace the source MAC address in the Ethernet header of an outgoing packet to make sure 
# the reply will be sent to the host interface. When Oracle VM VirtualBox sees an incoming packet with a destination IP address that belongs to one of the virtual machine adapters it replaces the destination
# MAC address in the Ethernet header with the VM adapter's MAC address and passes it on. Oracle VM VirtualBox examines ARP and DHCP packets in order to learn the IP addresses of virtual machines.


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
#		VBoxManage createhd --filename $BASEFOLDER/[VM]/[MACHINE NAME]_DISK.vdi --size 80000 --format VDI

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

#	VBoxManage createmedium --filename $BASEFOLDER/$VM/${VM}_DISK.vdi --size 8000 --format VDI
# -- size 8000 ends u with 7.8GB disc inside the VM

VBoxManage createmedium --filename $BASEFOLDER/$VM/${VM}_DISK.vdi --size 8192 --format VDI #--variant fixed
# 8192MB copied from a 8GB VDI created through GUI
# 8gib = 8192mib.

#	https://www.virtualbox.org/manual/ch08.html#vboxmanage-storagectl
VBoxManage storagectl $VM --name "SATA Controller" --add sata --controller IntelAhci
#	https://www.virtualbox.org/manual/ch08.html#vboxmanage-storageattach
VBoxManage storageattach $VM --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium  $BASEFOLDER/$VM/${VM}_DISK.vdi
VBoxManage storagectl $VM --name "IDE Controller" --add ide --controller PIIX4
#VBoxManage storageattach $VM --storagectl "IDE Controller" --port 1 --device 0 --type dvddrive --medium $ISO
VBoxManage modifyvm $VM --boot1 dvd --boot2 disk --boot3 none --boot4 none

#	https://superuser.com/questions/1453425/vboxmanage-unattended-installation-of-debian-ubuntu-waits-for-input
# aux_base_path="$(mktemp -d ${TMPDIR}/unattended-install-XXXXX)"
# VBoxManage unattended install $VM --auxiliary-base-path "$aux_base_path"/ --user=$USER --password=$PASSWORD --locale=en_UK --time-zone=UTC --iso=$ISO
# sed -i 's/^default vesa.*/default install/' "$aux_base_path"/isolinux-isolinux.cfg
# VBoxManage startvm $VM --type headless


VBoxManage unattended install $VM --user=$USER --password=$PASSWORD --locale=en_US --time-zone=UTC --iso=$ISO --package-selection-adjustment=minimal
# VBoxManage unattended install $VM --user=$USER --password=$PASSWORD --locale=en_US --time-zone=UTC --iso=$ISO --package-selection-adjustment=minimal --post-install-command="apt update && apt upgrade -y && apt install sudo -y"

# I use awk to get the UUID of the created VM and then use a patch file to fix a bug with unattended Debian installs.
# I also patch the generated preseed.cfg file to include the instructions for our desired partitioning.
UUID=$(vboxmanage list vms | awk -v vm="$VM" '{ gsub(/[{}]/, "", $0); } $1 ~ vm{ print $2; }')

# Without patch the unattended install launches graphical install instead of the standard install; and then gets stuck in region/language/country check.
patch /Users/mmakinen/VirtualBox\ VMs/$VM/Unattended-${UUID}-isolinux-txt.cfg < fix.patch

# The following adds our partitioning information into the preseed file for the automated installation of the Debian OS
patch /Users/mmakinen/VirtualBox\ VMs/$VM/Unattended-${UUID}-preseed.cfg < partition.patch

# Here we try to add our own commands into the postinstall script
# patch /Users/mmakinen/VirtualBox\ VMs/roger-skyline-1/Unattended-${UUID}-vboxpostinstall.sh < postinstall.patch 

# I echo the UUID to check that it was found properly and so that I can, if necessary, manually check that the patch went through.
echo $UUID

# Turn on VM
VBoxManage startvm $VM
# VBoxManage startvm $VM --type headless


# Turn off VM
# VBoxManage controlvm roger-skyline-1 poweroff

# /Users/mmakinen/VirtualBox VMs/roger-skyline-1

#	chipset PIIX3
#	I/O APIC Enabled
#	hardware clock in UTC time
#	2-3 cores
#	https://docs.oracle.com/en/virtualization/virtualbox/6.0/user/vboxmanage-list.html
#	https://www.openlogic.com/blog/how-use-vagrant-and-virtualbox

# apt update && apt upgrade -y && apt install sudo vim ufw fail2ban mailutils apache2 portsentry -y && sudo ufw limit 56789/tcp && sudo ufw allow 80/tcp && sudo ufw allow 443
# apt install net-tools

# sudo adduser mmak && sudo adduser mmak sudo
# auto enp0s3
#iface enp0s3 inet static
#	address 10.12.179.153
#	netmask 255.255.255.252
#	gateway 10.12.254.254

# attack user@10.12.179.154
# ssh-copy-id -i /Users/mmakinen/.ssh/id_rsa.pub mmakinen@10.12.179.153 -p 56789
# then logout and login.
# get ip with hostname -I then 'ssh user@<ip--addr>'


# ssh -p 56789 user@localhost

# sudo ufw default reject incoming && sudo ufw default allow outgoing && sudo ufw status verbose
# sudo ufw limit 56789/tcp && sudo ufw allow 80/tcp && sudo ufw allow 443

# sudo ufw reload && sudo systemctl restart fail2ban && sudo systemctl status fail2ban

# "ip route" gives good info about ip and gateway etc.
# Make changes in /etc/network/interfaces to turn off DHCP and use a static ip
# The primary network interface
# auto enp0s3
# iface enp0s3 inet static
#  address 10.11.198.126
#  netmask 255.255.255.25
#  gateway 10.11.254.254

# auto enp0s3
# iface enp0s3 inet static
# 	address 10.12.179.168
# 	netmask 255.255.255.252
# 	gateway 10.12.254.254

# sudo touch /var/log/update_script.log
# sudo chmod 755 /var/log/update_script.log

# #!/bin/bash
# printf "\n" >> /var/log/update_script.log
# date >> /var/log/update_script.log

# sudo apt-get update -y >> /var/log/update_script.log
# sudo apt-get upgrade -y >> /var/log/update_script.log

# sudo chmod 755 update.sh
# sudo chown root update.sh

# sudo crontab -e

# @reboot sudo ~/update.sh (for running it at boot)
# 0 4 * * 0 sudo ~/update.sh (for running it once a week, e.g. Sunday, at 4am)

# sudo systemctl enable cron


# sudo ufw limit 56789/tcp && sudo ufw allow 80/tcp && sudo ufw allow 443


# To create a self-signed SSL certificate in Debian with Apache2, you can use the openssl command-line tool. Here are the general steps to follow:

# Open a terminal and run the following command to create a private key for your certificate:
# openssl genrsa -out server.key 2048

# Use the private key to create a certificate signing request (CSR) file:
# openssl req -new -key server.key -out server.csr

# You will be prompted to enter information about your organization, 
# such as the common name (domain name) for the certificate.

# Use the CSR file to create a self-signed certificate:
# openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt

# Once you have your certificate and key files, you need to configure Apache to use them. On Debian and Ubuntu, Apache's configuration files are located in the /etc/apache2 directory.

# Open the default SSL virtual host configuration file using your preferred text editor:
# sudo vim /etc/apache2/sites-available/default-ssl.conf

# Find the <VirtualHost _default_:443> block and within it, 
# locate the lines that specify the paths to the SSL certificate and key files. 
# Replace the default paths with the paths to the server.crt and server.key files that you created earlier
# 
# Save the changes and exit the text editor.

# Enable the SSL module and the default-ssl site:
# sudo a2enmod ssl
# sudo a2ensite default-ssl

# Restart Apache for the changes to take effect:
# sudo service apache2 restart

# Now, you should be able to access your website using https:// and you can confirm the SSL certificate is self-signed by checking in the browser, it will show a warning message as the certificate is not verified by a trusted CA.

CHECK THE SIZE OF PARTITION:
* lsblk

CHECK THE SERVICES:
* systemctl list-units --type service --all --state active
* apt-get update && apt-get upgrade

CREATE A SUPERUSER
* sudo adduser temp && sudo adduser temp sudo

CHANGE THE SSHD_CONFIG
* sudo vim /etc/ssh/sshd_config
* sudo systemctl restart sshd && sudo systemctl status ssh
* ssh-keygen -f ~/.ssh/vmkey && ssh-add ~/.ssh/vmkey && ssh-copy-id -i ~/.ssh/vmkey temp@10.12.179.153 -p 56789
* ssh temp@10.12.179.153 -p 56789

CHANGE THE SSHD_CONFIG
* sudo vim /etc/ssh/sshd_config
    * comment and uncomment
* sudo systemctl restart sshd ; sudo systemctl status ssh

EXIT
* ssh temp@10.12.179.153 -p 56789

CHECK DCHP
* ip addr
* cat /etc/network/interfaces

CHANGE net mask
* sudo vim /etc/network/interfaces
* sudo systemctl restart networking.service
* ip addr

CHECK FIREWALL RULES
* sudo ufw status verbose
* sudo netstat -tulpn | grep LISTEN
* sudo systemctl list-unit-files --type service | grep "enabled "

OPEN ATTACK_VM
* ssh hacker@10.11.198.158
* ab -k -c 360 -n 20000 http://10.11.201.42
* sudo tail -F /var/log/fail2ban.log
* sudo fail2ban-client status http-get-dos
* sudo fail2ban-client status sshd
* sudo fail2ban-client banned

PORTS LISTENED and SCAN
* nmap 10.12.179.153
* sudo iptables --list | head

UP TO DATE?
* sudo apt update && sudo apt upgrade 

SCRIPT FOR UPDATES
* su -
* cd /root && ls
* cat update.sh

CRONTAB -e ( CHECK the last two lines)
* crontab -e

CRONTAB changed mail
* sudo vim /etc/crontab
* sudo bash /root/crontab_check.sh

https://10.12.179.153
systemctl list-units --type service --all --state active