ifconfig | grep -w ether | tr -d '\t\ \' | sed 's/ether//'
