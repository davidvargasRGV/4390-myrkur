# 4390-myrkur

This is the source code for the Senior Project assignment for CSCI 4390 Senior Project at the University of Texas Rio Grande Valley.

This project is a Malicious Direct Connect Client for the purpose of displaying the ease of which one could conduct DDoS attacks using malicious $ConnectToMe messages.

## Building

A makefile is provided. Simply execute the following...

```
make
```

The following is the directory structure...

* bin - C object files and Malicious Direct Connect Client binary
* doc - microdc2 scripts
* include/myrkur - C header files
* src - C source files

## Running

To execute the Malicious Direct Connect Client, simply execute the following... 

```
./bin/myrkur -i <host ip> -p <host port> -j <victim ip> -k <victim port>
```

The following options are available...

* -i, --hostip - Specify Direct Connect Hub IP Address
* -p, --hostport - Specify Direct Connect Hub Port Number
* -j, --victimip - Specify DDoS Victim IP Address
* -k, --victimport - Specify DDoS Victim Port Number
* -h, --help - Display this help message

## Example

**Note**: This project was tested with Apache 2.4.18, Open DC Hub 0.7.15, and microdc2 0.15.6.

To execute the Malicious Direct Connect Client, simply execute the following...

```
./bin/myrkur -i 192.168.1.20 -p 5000 -j 192.168.1.3 -k 3080
```

**Note**: In this case, Open DC Hub was at 192.168.1.20:5000 and the victim Apache2 Web Server was at 192.168.1.3:3080.

**Note**: Output is verbose. *For debugging purposes*.

## Authors

* David Vargas (*david.vargas.rgv [AT] gmail.com*)

## License

All rights reserved.

## Acknowledgments

None
