# Securely stream data from Arduino 101 with CAT 1 LTE Shield to Azure IoT Hub over HTTPS/REST

## PROJECT OWNER

Dave Glover | dglover@microsoft.com | @dglover

## COPYRIGHT

Free to use, reuse and modify, no liability accepted

## CREATED 

May 2017

## ACKNOWLEDGMENTS

This code builds on the [Telstra shield and connection library](https://github.com/telstra/TIC2017). 

### PURPOSE

This solution securely streams sensor data directly to 
[Azure IoT Hub](https://azure.microsoft.com/documentation/articles/iot-hub-what-is-iot-hub/?WT.mc_id=iot-0000-dglover) from a [Cat 1 IoT LTE](https://exchange.telstra.com.au/our-network-ready-to-support-the-internet-of-things/) Shield enabled Arduino.


### PLATFORM

This project was implemented and tested on the Arduino 101 with a Cat-1 Shield.

See [The Kit](https://github.com/telstra/TIC2017/wiki/1.-The-Kit)

![Cat1 Shield](https://raw.githubusercontent.com/gloveboxes/Arduino-101-Testra-Cat-1-LTE-Shield-Secure-Http-Azure-IoT-Hub-Client/master/Resources/Cat1Shield.jpg)

This solution streams sample sensor data securely over HTTPS / REST directly to Azure IoT Hub or Azure Event Hub.

### ARDUINO LIBRARIES

The following libraries are required.

Install Arduino Libraries from Sketch -> Include Library -> Manage Libraries

1. ArduinoJson
2. Time

### AZURE IOT HUB

IoT Hub is designed to "Connect, monitor, and control millions of IoT assets" and is
designed for internet scale data ingestion. 

[Stream Analytics](https://azure.microsoft.com/services/stream-analytics/?WT.mc_id=iot-0000-dglover), 
[Power Bi](https://powerbi.microsoft.com/?WT.mc_id=iot-0000-dglover) and preconfigured IoT Hub solutions such as 
[Remote monitoring ](https://azure.microsoft.com/documentation/articles/iot-suite-remote-monitoring-sample-walkthrough?WT.mc_id=iot-0000-dglover) provide ways to visualise and unlock the value of your data in Azure.

For more background information read this "[Stream Analytics & Power BI: A real-time analytics dashboard for streaming data](https://azure.microsoft.com/documentation/articles/stream-analytics-power-bi-dashboard/?WT.mc_id=iot-0000-dglover)" article.

# Solution Architecture

![Architecture](https://raw.githubusercontent.com/gloveboxes/Arduino-101-Testra-Cat-1-LTE-Shield-Secure-Http-Azure-IoT-Hub-Client/master/Resources/Architecture.jpg)

# Setup and Deployment Summary

1. Setup your Azure IoT Hub. There is a free 8000 message a day subscription to get started.
2. Register your device with Azure IoT Hub.
4. Update the main AzureClient.ino sketch
6. View data with Device Explorer
7. Optionally: Visualise your data in real time with Azure Stream Analytics and Power BI.


# Setting Up Azure IoT Hub

Follow lab [Setting Up Azure IoT](http://thinglabs.io/workshop/cs/nightlight/setup-azure-iot-hub/) to provision an Azure IoT Hub and an IoT Hub device. 

### Azure IoT Hub Connection String

Using Device Explorer generate a connection string and update the connection string variable in the AzureClient.ino file. Then upload the project to the Arduino 101.

### Shield Sensor

The solutions reads temperature and light levels from the Cat1 Shield.


# Viewing Data

From Device Explorer, head to the Data tab, select your device, enable consumer group then click Monitor.

![IoT Hub Data](https://raw.githubusercontent.com/gloveboxes/Arduino-NodeMCU-ESP8266-Secure-Azure-IoT-Hub-Client/master/AzureClient/Fritzing/IoTHubData.JPG)


# Visualising Data

## Azure Stream Analytics

[Azure Stream Analytics](https://azure.microsoft.com/services/stream-analytics/?WT.mc_id=iot-0000-dglover) enables you to gain 
real-time insights in to your device, sensor, infrastructure, and application data.

See the [Visualizing IoT Data](http://thinglabs.io/workshop/cs/nightlight/visualize-iot-with-powerbi/) lab.  Replace the query in that lab with the following and be sure to change the time zone to your local time zone offset.  Australia (AEDST) is currently +11 hours.

    SELECT
        iothub.connectiondeviceid deviceid,
        Geo AS GeoLocation,
        Max(DateAdd(Hour, 10, EventEnqueuedUtcTime)) AS TimeCreated, -- AU EST UTC + 10
        Avg(Celsius) AS Temperature,
        AVG(Humidity) AS Humidity,
        AVG(Light) AS Light,
        AVG(HPa) AS AirPressure
    INTO
        [PowerBI]
    FROM
        [TelemetryHUB] TIMESTAMP BY EventEnqueuedUtcTime
    GROUP BY
        iothub.connectiondeviceid, Geo,
        TumblingWindow(minute, 30)

 
## Power BI

[Microsoft Power BI](https://powerbi.microsoft.com/?WT.mc_id=iot-0000-dglover) makes it easy to visualise, organize and better understand your data.

Follow the notes in the See the [Visualizing IoT Data](http://thinglabs.io/workshop/cs/nightlight/visualize-iot-with-powerbi/) lab and modify the real time report as per this image.

### Power BI Designer Setup

![Power BI Designer Setup](https://raw.githubusercontent.com/gloveboxes/Arduino-NodeMCU-ESP8266-Secure-Azure-IoT-Hub-Client/master/AzureClient/Fritzing/PowerBIDesigner.JPG)


### Power BI Report Viewer

View on the web or with the Power BI apps available on iOS, Android and Windows.

![Power BI Report Viewer](https://raw.githubusercontent.com/gloveboxes/Arduino-NodeMCU-ESP8266-Secure-Azure-IoT-Hub-Client/master/AzureClient/Fritzing/PowerBIReport.JPG)



# Data Schema

The AzureClient sketch streams data in the following JSON format, of course you can change this:)

    {"Celsius":25.00,"Humidity":50.00,"hPa":1000,"Light":0,"Geo":"Sydney","Schema":1,"Id":2}


## Arduino IDE

As at May 2017 use:-

1. [Arduino IDE 1.8.2](https://www.arduino.cc/en/Main/Software).

## Visual Studio Code

For a better IDE experience consider installing [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=iot-0000-dglover)

Add the following Extensions

1. [Microsoft C/C++]()
2. [Microsoft Ardiuno]()

