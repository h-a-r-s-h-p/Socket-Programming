#!/bin/bash
# Script to stop the VMs
echo "Stopping the VMs..."
VMs="h1 r1 r2"
for vm in $VMs; do
	echo "Powering down $vm..."
	VBoxManage controlvm "$vm" poweroff
	sleep 1
done
