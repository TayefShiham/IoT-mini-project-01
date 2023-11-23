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

We installed a local MQTT broker called mosquitto with the following command :

```
sudo apt install mosquitto
```

Note : the DNF PKG Manager might not work with your linux distro,use the native PKG manager of your operating system to install mosquitto.

To configure the broker on localhost to transmit data to AWS,execute this command :

```
sudo nano /etc/mosquitto/conf.d/bridge.conf
```

This will start the nano text editor which comes pre installed with maximum linux distros. Alternatively you can use VIM but we don't know how to exit it so not recommended. Insert the following configurtion in the text file and don't forget to replace the phaceholders with proper creds from AWS.

```
script here
```

Note : Don't forget to save while exiting nano.