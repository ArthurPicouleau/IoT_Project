# IoT_Project : Janne Uutela, Dimitrios Primpas and Arthur Picouleau


We started with the idea of developing an application for a weather station. We therefore looked for a card with temperature, pressure and luminosity sensors.
We decided to use the IOT_LAB M3 board because it contains all the sensors we need. 
With this card, we have access to a luminosity sensor (ISL29020), a pressure sensor and a temperature sensor (LPS331AP), which is exactly what we needed for our weather station application.
To develop our application we used RIOT OS on IoT-LAB.

## Part 1 : Sensors ##

To run the code to retrieve data from the sensors, you need to go to the Jupyter Lab server on IoT-LAB.
Next, create a folder within the riot/basics (in lowercase) folder. You can create your folder in other place but don't forget to change the path in the makefile. Put in the main.c and Makefile files provided in the Sensors folder, in the Github repository.
Then open a terminal and go to the folder containing the main.c file.
Select an environment with the following command :
```
env SITE=saclay
```
In our case, we have always chosen the saclay site. 
```
iotlab-experiment submit -n "sensors_data" -d 20 -l 1,archi=m3:at86rf231+site=saclay
```
Here the experiment will last 20 minutes. This value can be modified. Similarly, the site can be changed by modifying the value of the SITE variable in the command. 
Then write the following command:
```
iotlab-experiment wait --timeout 30 --cancel-on-timeout
```
We are waiting for the experiment to switch to "Running" status.

```
make BOARD=iotlab-m3 IOTLAB_NODE=auto flash
```

To see the results, go to the "My experiments" section on Iot-LAB.
You will get the following result:
![Image1](/Sensors/Experiments.PNG)

Click on the arrow next to running and then on "View Details".
You will then get the following page:

![Image2](/Sensors/Terminal.PNG)

Finally, in the "Action" section, click on "Open Terminal". You will then see the sensor values appear:

![Image3](/Sensors/Results.PNG)

## Part 2 : COAP Communication ##

Secondly, we tried to communicate between two IOT LAB nodes using the Coap protocol.
Before starting, make sure that the first experiment has been completed or stopped.

Create a new folder within the riot folder. Then copy the main.c file, the Makefile, the gcoap_cli.c and the .ipynb file into your .

Open two terminals in Jupyter and go to the folder containing the main.c file.
In one of the terminals type the following 4 commands:

```
env SITE=saclay
```
```
iotlab-experiment submit -n "riot-coap" -d 60 -l 2,archi=m3:at86rf231+site=saclay
```
```
iotlab-experiment wait --timeout 30 --cancel-on-timeout
```
```
iotlab-experiment --jmespath="items[*].network_address | sort(@)" get --nodes
```
If you want you can choose: lille, paris, strasbourg, grenoble.
Then open the .ipynb file, which is a Jupyter notebook. Run the code. You will obtain two values: CHANNEL ID and PAN_ID, which are essential for establishing communication.
Here you can see an example of values :

![Image4](/COAP_Communication/Notebook_example.PNG)

Then, in the first terminal, type the following command:

```
make DEFAULT_CHANNEL=<channel> DEFAULT_PAN_ID=<pan_id> IOTLAB_NODE=m3-<id>.<site>.iot-lab.info -C. flash term
```

Replace ```<channel>```  and ```<pan_id>``` with the values obtained using the notebook. Then the value of ```<site>``` and ```<id>``` by the name and value of the node obtained by the fourth command.

In the second, type the same command but change the ```<id>``` of the site. Take the second node.
Here,you can see the two nodes in the IOT-LAB:

![Image5](/COAP_Communication/Coap.PNG)

In the first terminal, which we will now call the coap server, you can type the following command: 
```
ifconfig
```
to obtain the IP V6 address of the coap server.

You can also use the ```coap info``` command :

```
coap info
```
to obtain the port on which the server is listening. By default, the server listens on port 5683

You can then test communication with the second node, the coap client, by typing in the second terminal the following command ```ping``` followed by the server's IPV6 address.

Finally, to retrieve the temperature values from the sensor, you can type the following command:
```
coap get <ip_v6> : 5683 /temperature
```
You have just to replace ```<ip_v6>``` by the IP V6 adress of the server.

Here, you can see the results with the temperature.

![Image6](/COAP_Communication/Results_Coap.PNG)

We only succeeded in communicating the temperature. 
When we test with brightness and pressure we get the following result:

![Image6](/COAP_Communication/Results_Coap2.PNG)

## Part 3 : MQTT Communication ##

We also tried mqtt communication, but we were unable to send a mqtt message from the board to any broker. However, we tested and set up mqtt bridge
connecting to AWS, incase we succeed in sending the message to iotlab mqtt broker, or to our own broker, from the board. Below you can see that we bridged some topic 
for testing purposes that was being posted to mosquitto broker, to our controlled AWS iot-core. AWS seems to have strict security and so that a device
can connect to AWS, it needs to have the certificates and private keys, which we setup to our bridge.

![Image7](/MQTT_Communication/mqtt_bridge.png)

The messages were received in our iot-core test client, after setting up the security policy allowing our bridge to connect and publish to it.
You can adjust your security policies in aws iot-core security -> policies panel.

![Image7](/MQTT_Communication/aws_iot_core.png)


## Part 4 : Demonstration video ##

[Demonstration video]
(https://youtu.be/pKcicKqbMaU)
