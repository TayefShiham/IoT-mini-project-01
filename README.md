# IoT-mini-project-01

## Step 0 : Localhost and Host OS Config

Any machine made after the fall of soviet union should work as long as in can be interfaced with. Here are the specs of the computer we used for this project : 

```
             /////////////                tayef@pop-os 
         /////////////////////            ------------- 
      ///////*767////////////////         OS: Pop!_OS 22.04 LTS x86_64 
    //////7676767676*//////////////       Host: X58 
   /////76767//7676767//////////////      Kernel: 6.5.6-76060506-generic 
  /////767676///*76767///////////////     Disk: 11G / 113G (11%)
 ///////767676///76767.///7676*///////    Packages: 1914 (dpkg) 
/////////767676//76767///767676////////   Shell: bash 5.1.16 
//////////76767676767////76767/////////   Resolution: 1440x900, 1440x900 
///////////76767676//////7676//////////   DE: Unity 
////////////,7676,///////767///////////   WM: Mutter 
/////////////*7676///////76////////////   WM Theme: Adwaita 
///////////////7676////////////////////   Theme: Adwaita [GTK2/3] 
 ///////////////7676///767////////////    Icons: Adwaita [GTK2/3] 
  //////////////////////'////////////     Terminal: vscode 
   //////.7676767676767676767,//////      CPU: Intel Xeon X5675 (12) @ 3.068GHz 
    /////767676767676767676767/////       GPU: AMD ATI Radeon HD 5550/5570/5630/6510/6610/7570 
      ///////////////////////////         Memory: 2060MiB / 3893MiB 
         /////////////////////
             /////////////                                        
                                                                  
```

The codebase should work out of the box on other Linux systems with DNF,Pacman,YUM and other PKG managers as long as the upcoming steps are followed properly. On Windows NT family OS, please set up the Windows Subsystem for Linux. For MacOS ,please stop reading this and pick a different profession.

Note : Don't switch to root to save time,if you do you're going to have a very bad time later on.

## Step 1 : Setup MQTT broker

We installed a local MQTT broker called [mosquitto.rsmb](https://github.com/eclipse/mosquitto.rsmb) which is a tiny version of the original [ Mosquitto](https://mosquitto.org/) is that Mosquitto doesn't currently have support for the MQTT-SN protocol,which the RSMB version does. Clone it from the github repository by executing this command :

```
git clone https://github.com/eclipse/mosquitto.rsmb.git
```

Note : Git usually comes preinstalled in most of the Linux distros. If it didn't come with yours and you don't know how to install it,then we suggest that you change your major.

To install the broker on localhost,first navigate to the child directory :

```
cd mosquitto.rsmb/rsmb/src
```

Then start the build process with this command :
```
make
```
When the build process is finished, make a configuration file to store the script in the same directory.
```
nano config.conf
```
This will start the nano text editor which comes pre installed with maximum linux distros. Alternatively you can use VIM but we don't know how to exit it so not recommended. Insert the following configurtion in the file editor :

```
# add some debug output
trace_output protocol
# listen for MQTT-SN traffic on UDP port 1885
listener 1885 INADDR_ANY mqtts
ipv6 true
# listen to MQTT connections on tcp port 1886
listener 1886 INADDR_ANY
ipv6 true
```

Note : Don't forget to save the changes while exiting nano. We could add the shortcuts and details but it might offend smart people so we opted to add only the minimum to replicate the process.

After saving the config,start the broker with this command :
```
./broker_mqtts config.conf
```

Note : Be mindful of your current directory in the CLI. If you're in the wrong folder then the command won't work since the terminal won't know what you're talking about.

If you've done everything right, then the CLI output should look exactly like this :
```
20231123 093216.766 CWNAN9999I Really Small Message Broker
20231123 093216.766 CWNAN9998I Part of Project Mosquitto in Eclipse
(http://projects.eclipse.org/projects/technology.mosquitto)
20231123 093216.766 CWNAN0049I Configuration file name is config.conf
20231123 093216.766 CWNAN0053I Version 1.3.0.2, Nov 23 2023 07:57:24
20231123 093216.766 CWNAN0054I Features included: bridge MQTTS 
20231123 093216.766 CWNAN9993I Authors: Ian Craggs (icraggs@uk.ibm.com), Nicholas O'Leary
20231123 093216.766 CWNAN0300I MQTT-S protocol starting, listening on port 1885
20231123 093216.766 CWNAN0014I MQTT protocol starting, listening on port 1886
```

Note : The current terminal window is running the program we need to be operational throughout the task,so don't terminate it and use a new terminal window to continue the next step. Take care not to get lost in the process, we will start from the parent folder of this repository.