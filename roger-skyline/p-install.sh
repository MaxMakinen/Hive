#!/bin/bash

# get our apt up to speed
echo "p4ssw0rd" | su -c "apt update && apt upgrade -y"
# add /sbin into our PATH so that we can call functions easier
echo "p4ssw0rd" | su -c "echo 'export PATH="/sbin:$PATH"' >> .bashrc"
echo "p4ssw0rd" | su -c "source .bashrc"
# install sudo and add user to group
echo "p4ssw0rd" | su -c "apt install sudo -y"
echo "p4ssw0rd" | su -c "adduser user sudo"
# install net-tools for network shenanigans
echo "p4ssw0rd" | su -c "apt install net-tools -y"
# install ufw (uncomplicated firewall) for the project
echo "p4ssw0rd" | su -c "apt install ufw -y"
# install fail2ban to protect ourselves from slowloris attack
echo "p4ssw0rd" | su -c "apt install fail2ban -y"
