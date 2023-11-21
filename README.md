# IoT_Project

We started with the idea of developing an application for a weather station. We therefore looked for a card with temperature, pressure and luminosity sensors.
We decided to use the IOT_LAB M3 board because it contains all the sensors we need. 
With this card, we have access to a luminosity sensor (ISL29020), a pressure sensor and a temperature sensor (LPS331AP), which is exactly what we needed for our weather station application.
To develop our application we used RIOT OS on IoT-LAB.

To run the code to retrieve data from the sensors, you need to go to the Jupyter Lab server on IoT-LAB.
Next, create a folder within the riot folder. Put in the main.c and Makefile files provided in the Sensors folder, in the Github repository.
Then open a terminal and go to the folder containing the main.c file.
Select an environment with the following command :
```
env SITE=saclay
```
In our case, we have always chosen the grenoble site. You can choose: lille, paris, strasbourg, grenoble.
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


Secondly, we tried to communicate between two IOT LAB nodes using the Coap protocol.

Create a new folder within the riot folder. Then copy the main.c file, the Makefile and the .ipynb file into your .

Open two terminals and go to the folder containing the main.c file.
In one of the terminals type the following 4 commands:

```
env SITE=saclay
```
```
iotlab-experiment submit -n "riot-coap" -d 60 -l 2,archi=m3:at86rf231+site=saclay
```
```
iotlab-experiment wait --timeout 30 --cancel-on-timeou
```
```
iotlab-experiment --jmespath="items[*].network_address | sort(@)" get --nodes
```

Then open the .ipynb file, which is a Jupyter notebook. Run the code. You will obtain two values: CHANNEL ID and PAN_ID, which are essential for establishing communication.
Here you can see an example of values :

![Image4](/COAP_Communication/Notebook_example.PNG)

Then, in the first terminal, type the following command:

```
make DEFAULT_CHANNEL=<channel> DEFAULT_PAN_ID=<pan_id> IOTLAB_NODE=m3-<id>.<site>.iot-lab.info -C. flash term
```

Replace  <channel>  and <pan_id> with the values obtained using the notebook. Then the value of <site> and <id> by the name and value of the node obtained by the fourth command.

In the second type the same command but change the <id> of the site. Take the second node.




