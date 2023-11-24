# IoT-mini-project-01

## Step 0 : Localhost and Host OS Config

Any machine made after the fall of the soviet union should work as long as it can be interfaced with. Here are the specs of the computer we used for this project : 

```bash
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

We installed a local MQTT broker called [mosquitto.rsmb](https://github.com/eclipse/mosquitto.rsmb) which is a tiny version of the original [ Mosquitto](https://mosquitto.org/) is that Mosquitto doesn't currently have support for the MQTT-SN protocol,which the RSMB version does. Clone it from the GitHub repository by executing this command :

```bash
git clone https://github.com/eclipse/mosquitto.rsmb.git
```

Note : Git usually comes preinstalled in most of the Linux distros. If it didn't come with yours and you don't know how to install it,then we suggest that you change your major.

To install the broker on localhost,first navigate to the child directory :

```bash
cd mosquitto.rsmb/rsmb/src
```

Then start the build process with this command :

```bash
make
```

When the build process is finished, make a configuration file to store the script in the same directory.

```bash
nano config.conf
```
This will start the nano text editor which comes pre-installed with maximum Linux distros. Alternatively, you can use VIM but we don't know how to exit it so not recommended. Insert the following configuration in the file editor :

```c
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

```bash
./broker_mqtts config.conf
```

Note : Be mindful of your current directory in the CLI. If you're in the wrong folder then the command won't work since the terminal won't know what you're talking about.

If you've done everything right, then the CLI output should look exactly like this :

```bash
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

# Step 2 : RIOT

Clone the RIOT-OS from the official repository on your localhost :

```bash
git clone https://github.com/RIOT-OS/RIOT.git
```

The repository is quite large with close to 347452 objects so it is likely to take a while depending on your internet speed. The output should look similar to this :

```bash
Cloning into 'RIOT'...
remote: Enumerating objects: 347452, done.
remote: Counting objects: 100% (106992/106992), done.
remote: Compressing objects: 100% (9742/9742), done.
remote: Total 347452 (delta 101975), reused 97419 (delta 97243), pack-reused 240460
Receiving objects: 100% (347452/347452), 130.73 MiB | 1.14 MiB/s, done.
Resolving deltas: 100% (238801/238801), done.
Updating files: 100% (15941/15941), done.
```
After cloning the repository, a new directory named *emcute_MQTTSN* has to be created in the *examples* subdirectory of the RIOT. The directory must contain this Makefile named as such :

```Makefile
# name of your application
APPLICATION = emcute_mqttsn

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Specify the mandatory networking modules for IPv6 and UDP
USEMODULE += gnrc_sock_udp
USEMODULE += gnrc_ipv6_default
# Include MQTT-SN
USEMODULE += emcute
# Add also the shell, some shell commands
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
# For testing we also include the ping6 command and some stats
USEMODULE += gnrc_icmpv6_echo
# For measuring time
USEMODULE += xtimer

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Comment this out to join RPL DODAGs even if DIOs do not contain
# DODAG Configuration Options (see the doc for more info)
# CFLAGS += -DGNRC_RPL_DODAG_CONF_OPTIONAL_ON_JOIN

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

```

Along with these for a main.c file in the same parent directory:

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// libraries added
#include <time.h>

#include "shell.h"
#include "msg.h"
#include "net/emcute.h"
#include "net/ipv6/addr.h"

#ifndef EMCUTE_ID
#define EMCUTE_ID ("gertrud")
#endif
#define EMCUTE_PORT (1883U)
#define EMCUTE_PRIO (THREAD_PRIORITY_MAIN - 1)

static char stack[THREAD_STACKSIZE_DEFAULT];
static msg_t queue[8];

// struct that contains sensors
typedef struct sensors{
  int temperature;
  int humidity;
  int windDirection;
  int windIntensity;
  int rainHeight;
}t_sensors;

static void *emcute_thread(void *arg)
{
    (void)arg;
    emcute_run(EMCUTE_PORT, EMCUTE_ID);
    return NULL; /* should never be reached */
}

// function that disconnects from the mqttsn gateway
static int discon(void){
    int res = emcute_discon();
    if (res == EMCUTE_NOGW) {
        puts("error: not connected to any broker");
        return 1;
    }
    else if (res != EMCUTE_OK) {
        puts("error: unable to disconnect");
        return 1;
    }
    puts("Disconnect successful");
    return 0;
}

// function that publish messages to the topic
// it takes as input the topic, the message to send and
// the value of qos
static int pub(char* topic, char* data, int qos){
  emcute_topic_t t;
  unsigned flags = EMCUTE_QOS_0;

  switch (qos) {
      case 1:
        flags |= EMCUTE_QOS_1;
        break;
      case 2:
        flags |= EMCUTE_QOS_2;
        break;
      default:
        flags |= EMCUTE_QOS_0;
        break;
  }



  /* step 1: get topic id */
  t.name = topic;
  if (emcute_reg(&t) != EMCUTE_OK) {
      puts("error: unable to obtain topic ID");
      return 1;
  }

  /* step 2: publish data */
  if (emcute_pub(&t, data, strlen(data), flags) != EMCUTE_OK) {
      printf("error: unable to publish data to topic '%s [%i]'\n",
              t.name, (int)t.id);
      return 1;
  }

  printf("published %s on topic %s\n", data, topic);

  return 0;
}

// function that connects to the mqtt gateway
// it takes as input the ip address and the port
static int con(char* addr, int port){
  sock_udp_ep_t gw = { .family = AF_INET6, .port = EMCUTE_PORT };
  gw.port = port;

  /* parse address */
  if (ipv6_addr_from_str((ipv6_addr_t *)&gw.addr.ipv6, addr) == NULL) {
      printf("error parsing IPv6 address\n");
      return 1;
  }

  if (emcute_con(&gw, true, NULL, NULL, 0, 0) != EMCUTE_OK) {
      printf("error: unable to connect to [%s]:%i\n", addr, port);
      return 1;
  }
  printf("Successfully connected to gateway at [%s]:%i\n", addr, port);
  return 0;
}

// function that computes random values in the specified range
int rand_val(int min, int max){
  srand(time(NULL));
  return (rand() % (int)((max-min+1) * 100)) / 100 + min;
}

// function that generate sensor values
static void gen_sensors_values(t_sensors* sensors){
  sensors->temperature = rand_val(-50,50);
  sensors->humidity = rand_val(0, 100);
  sensors->windDirection = rand_val(0, 360);
  sensors->windIntensity = rand_val(0, 100);
  sensors->rainHeight = rand_val(0, 50);
}

// new shell command: start the station
// the function takes in input ip address and port of the gateway,
// and the id of the specified station
// every five seconds it generates new sensor values and publish them to 
// sensor/station + station id
static int cmd_start(int argc, char **argv){
  if (argc < 4) {
      printf("usage: %s <address> <port> <id>\n", argv[0]);
      return 1;
  }
  // sensors struct
  t_sensors sensors;
  // name of the topic
  char topic[32];
  sprintf(topic,"sensor/station%d", atoi(argv[3]));
  
  // json that it will published
  char json[128];
  
  while(1){
    // it tries to connect to the gateway
    if (con(argv[1], atoi(argv[2]))) {
      continue;
    }
    
    // takes the current date and time
    char datetime[20];
    time_t current;
    time(&current);
    struct tm* t = localtime(&current);
    int c = strftime(datetime, sizeof(datetime), "%Y-%m-%d %T", t);
    if(c == 0) {
      printf("Error! Invalid format\n");
      return 0;
    } 

    // updates sensor values
    gen_sensors_values(&sensors);

    // fills the json document
    sprintf(json, "{\"id\": \"%d\", \"datetime\": \"%s\", \"temperature\": "
                  "\"%d\", \"humidity\": \"%d\", \"windDirection\": \"%d\", "
                  "\"windIntensity\": \"%d\", \"rainHeight\": \"%d\"}",
                  atoi(argv[3]), datetime, sensors.temperature, sensors.humidity, 
                  sensors.windDirection, sensors.windIntensity, sensors.rainHeight);
      
    // publish to the topic
    pub(topic, json, 0);

    // it disconnects from the gateway
    discon();

    // it sleeps for five seconds
    xtimer_sleep(5);
  }

  return 0;
}

static const shell_command_t shell_commands[] = {
    {"start", "Start the station", cmd_start},
    {NULL, NULL, NULL}};

int main(void)
{
    puts("MQTT-SN application\n");
    puts("Type 'help' to get started. Have a look at the README.md for more "
         "information.");

    /* the main thread needs a msg queue to be able to run `ping6`*/
    msg_init_queue(queue, ARRAY_SIZE(queue));

    /* start the emcute thread */
    thread_create(stack, sizeof(stack), EMCUTE_PRIO, 0,
                  emcute_thread, NULL, "emcute");

    /* start shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should be never reached */
    return 0;
}

```

Note : If the parent directory is to be changed for some reson, the **RIOTBASE** properties in the *Makefile* must also be adjusted with the new address.

Make sure that the broker is running in the other terminal and setup the interfaces and the bridge using RIOT's tapsetup script:

```bash
sudo ./RIOT/dist/tools/tapsetup/tapsetup -c 2
```

The command should produce this output :

```bash
creating bridge tapbr0
creating tap0
creating tap1
```

After the creation of the bridge, assign a site-global prefix to the tapbr0 interface:

```bash
sudo ip a a fec0:affe::1/64 dev tapbr0
```

Navigate to the *emcute_MQTTSN* directory in a new terminal and execute this command :

```bash
make all term PORT=tap0
```
Rollback to the terminal with the project directory and assign a site-global address :

```bash
ifconfig 5 add fec0:affe::99
```
Now that the application interface is open, communication with the broker can be initiated.




















