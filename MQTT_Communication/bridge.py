import paho.mqtt.client as mqtt

# Callback function for receiving and printing messages
def on_message(client, userdata, message):
    print(f"Received message: {message.payload.decode()} on topic {message.topic}")
    data = client.destination_client.publish("ourdevice/var", message.payload.decode())
    print('data back--',data, data.is_published())

def on_connect(client, userdata, flags, rc):
    print('connected--', client, userdata, flags, rc)

destination_client = mqtt.Client("your_client_name")
# paths to your device certificates
ca_certification = "./certs/AmazonRootCA1.pem"
certification = "./certs/your_device-certificate.pem.crt"
private_key = "./certs/your_device-private.pem.key"

destination_client.tls_set(ca_certs=ca_certification, certfile=certification, keyfile=private_key)
destination_client.on_connect = on_connect
destination_client.connect("your_aws_endpoint", 8883)

# Source MQTT broker configuration
source_client = mqtt.Client()
source_client.destination_client = destination_client
source_client.on_message = on_message

# Source broker connection
source_client.connect("test.mosquitto.org", 1883)
source_client.subscribe("some/topic")
source_client.loop_forever()


try:
    while True:
        pass

except KeyboardInterrupt:
    source_client.disconnect()
    destination_client.disconnect()
