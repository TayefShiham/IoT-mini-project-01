# IoT-mini-project-01

## Step 0 : Localhost and Host OS Config

Any machine made after the fall of soviet union should work as long as in can be interfaced with. Here are the specs of the computer we used for this project : 

```
             .',;::::;,'.                tayef@kg-06sleipnir 
         .';:cccccccccccc:;,.            ------------------- 
      .;cccccccccccccccccccccc;.         OS: Fedora Linux 38 (Workstation Edition) x86_64 
    .:cccccccccccccccccccccccccc:.       Host: Vostro 14-3468 
  .;ccccccccccccc;.:dddl:.;ccccccc;.     Kernel: 6.5.10-200.fc38.x86_64 
 .:ccccccccccccc;OWMKOOXMWd;ccccccc:.    Terminal: vscode 
.:ccccccccccccc;KMMc;cc;xMMc:ccccccc:.   Packages: 2025 (rpm), 10 (flatpak) 
,cccccccccccccc;MMM.;cc;;WW::cccccccc,   Shell: bash 5.2.15 
:cccccccccccccc;MMM.;cccccccccccccccc:   Resolution: 4246x900
:ccccccc;oxOOOo;MMM0OOk.;cccccccccccc:   DE: GNOME 44.6 
cccccc:0MMKxdd:;MMMkddc.;cccccccccccc;   WM: Mutter 
ccccc:XM0';cccc;MMM.;cccccccccccccccc'   WM Theme: Adwaita 
ccccc;MMo;ccccc;MMW.;ccccccccccccccc;    Theme: Adwaita-dark [GTK2/3] 
ccccc;0MNc.ccc.xMMd:ccccccccccccccc;     Icons: Adwaita [GTK2/3] 
cccccc;dNMWXXXWM0::cccccccccccccc:,      Disk: 97G / 237G (42%)
cccccccc;.:odl:.;cccccccccccccc:,.       CPU: Intel i3-7100U (4) @ 2.400GHz 
:cccccccccccccccccccccccccccc:'.         GPU: Intel HD Graphics 620 
.:cccccccccccccccccccccc:;,..            Memory: 7793MiB 
  '::cccccccccccccc::;,.
```

The codebase should work out of the box on other Linux systems with Apt,Pacman,YUM and other PKG managers as long as the upcoming steps are followed properly. On Windows NT family OS, please set up the Windows Subsystem for Linux. For MacOS ,please stop reading this and pick a different profession.

Note : Don't switch to root to save time,if you do you're going to have a very bad time later on.

## Step 1 : Setup MQTT broker

We installed a local MQTT broker called mosquitto with the following command :

```
sudo dnf install mosquitto
```

Note : the DNF PKG Manager might not work with your linux distro,use the native PKG manager of your operating system to install mosquitto.

To configure the broker on localhost to transmit data to AWS,execute this command :

```
sudo nano /etc/mosquitto/conf.d/bridge.conf
```

This will start the nano text editor which comes pre installed with maximum linux distros. Alternatively you can use VIM but we don't know how to exit it so not recommended. Insert the following configurtion in the text file and don't forget to replace the phaceholders with proper creds from AWS.

```
#Copy paste the following in the nano editor:
# =================================================================
# Bridges to AWS IOT
# =================================================================

# AWS IoT endpoint, use AWS CLI 'aws iot describe-endpoint'
connection awsiot
address ***********-ats.iot.us-east-1.amazonaws.com:8883

# Specifying which topics are bridged
topic awsiot_to_localgateway in 1
topic localgateway_to_awsiot out 1
topic topic both 1
try_private false
# Setting protocol version explicitly
bridge_protocol_version mqttv311
bridge_insecure false

# Bridge connection name and MQTT client Id,
# enabling the connection automatically when the broker starts.
cleansession true
clientid bridgeawsiot
start_type automatic
notifications false
log_type all

# =================================================================
# Certificate based SSL/TLS support
# -----------------------------------------------------------------
#Path to the rootCA
bridge_cafile /home/giuliano/Desktop/IOT/cert/root-CA.crt

# Path to the PEM encoded client certificate
bridge_certfile /home/giuliano/Desktop/IOT/cert/*********-certificate.pem.crt

# Path to the PEM encoded client private key
bridge_keyfile /home/giuliano/Desktop/IOT/cert/*********-private.pem.key
```

Note : Don't forget to save while exiting nano.