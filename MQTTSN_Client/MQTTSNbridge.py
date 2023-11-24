from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient
import MQTTSNclient
import json
import boto3

# Connection to DynamoDB and access to the table EnvironmentalStationDB
dynamodb = boto3.resource('dynamodb', region_name='us-east-1')
dynamoTable = dynamodb.Table('EnvironmentalStationDB')
jsonP = ''  # Variable to store JSON payload

# Instantiate MQTT and MQTT-SN clients
MQTTClient = AWSIoTMQTTClient("MQTTSNbridge")
MQTTSNClient = MQTTSNclient.Client("bridge", port=1885)

class Callback:
    # Function that handles incoming messages from the MQTT-SN broker
    # It publishes the message to the MQTT broker and stores it in DynamoDB
    def messageArrived(self, topicName, payload, qos, retained, msgid):
        # Decode the payload and load it as JSON
        message = payload.decode("utf-8")
        jsonP = json.loads(message)  # Update global JSON payload variable
        print(topicName, message)  # Print received topic and message
        MQTTClient.publish(topicName, message, qos)  # Publish the message to MQTT broker
        dynamoTable.put_item(Item=jsonP)  # Store the message payload in DynamoDB
        return True

# Path indicating the certificates position
path = "../certs/"

# Configure access to the AWS MQTT broker
MQTTClient.configureEndpoint("apikey", 8883)
MQTTClient.configureCredentials(
    path + "root-CA.crt",
    path + "private.pem.key",
    path + "certificate.pem.crt"
)

# Configure MQTT client settings
MQTTClient.configureOfflinePublishQueueing(-1)  # Infinite offline Publish queueing
MQTTClient.configureDrainingFrequency(2)  # Draining: 2 Hz
MQTTClient.configureConnectDisconnectTimeout(10)  # 10 sec
MQTTClient.configureMQTTOperationTimeout(5)  # 5 sec

# Register the callback for MQTT-SN client
MQTTSNClient.registerCallback(Callback())

# Establish connections to the MQTT and MQTT-SN brokers
MQTTClient.connect()
MQTTSNClient.connect()

# Ask the user for station IDs to subscribe to
station_ids = ""
print("Enter the ID of the station to subscribe to. Type 'stop' to interrupt.\n")
while True:
    current_id = input("")
    if current_id == 'stop':
        break
    else:
        station_ids += current_id + " "

# Subscribe to the topics chosen by the user
for id in station_ids.split():
    MQTTSNClient.subscribe("sensor/station" + id)
print("Subscribed to stations with ID: " + station_ids)

# Wait for a command to exit the program
while True:
    if input("Enter 'quit' to exit from the program.\n") == "quit":
        break

# Disconnect from the MQTT and MQTT-SN clients
MQTTSNClient.disconnect()
MQTTClient.disconnect()
