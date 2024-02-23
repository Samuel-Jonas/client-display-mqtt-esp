# client-display-mqtt-esp
Display controled by ESP32 using MQTT protocol

<a name="readme-top"></a>

[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Samuel-Jonas/client-display-mqtt-esp">
    <img src="images/mqtt_icon.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">ESP32 MQTT Broker</h3>

  <p align="center">
    A challenge for Embedded Software Engineer Junior role
    <br />
    <a href="https://github.com/Samuel-Jonas/client-display-mqtt-esp>
    <strong>Explore the docs »</strong>
    </a>
    <br />
    <br />
    <a href="https://github.com/Samuel-Jonas/client-display-mqtt-esp">View Demo</a>
    ·
    <a href="https://github.com/Samuel-Jonas/sensor-flow">Another project</a>
    ·
    <a href="https://github.com/Samuel-Jonas/broker-mqtt-esp">Releated Project</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#unit-test">Unit Test Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![MQTT Broker ESP32][product-screenshot]](https://github.com/Samuel-Jonas/client-display-mqtt-esp)

To develop quickly I decided to abstract the responsibilities of building with makefile to this VSCode extension, so I just need to focus on the evaluation requirements and improve my README file for a better explanation.

Assessment requirements:

> 1. Select a target hardware platform (e.g., Raspberry Pi, BeagleBone, etc.)
>
> 2. Configure it to have a mosquitto (MQTT) local broker running.
>
> 3. Develop a Hardware Abstraction Layer (HAL) header file to abstract the display.
>
> 4. Develop a library that implements the HAL for the selected display, based on the communication > protocol it uses.
>
> 5. Develop a program and link it to the created library. It should listen to the "/test/trimble" MQTT topic, and every time a json message in the format "{ "print": "MESSAGE" }" is received it should print the message into the display.
>
> 6. Develop another program that publishes the amount of seconds it has been running in the "/test/trimble" MQTT topic every 10 seconds, so that the information is printed on the display.
>
> 7. Write unit tests for your code.

Briefly for my solution to be accordingly with the assessment requirements I've been assuming this:

* I'm using ESP32 DevKit V1 as the target hardware platform.

* To configure a broker running on ESP32 I'm just using the library **sMQTTBroker.h**.

* An LCD display 16x2 with an I2C module will be used to display the content of this JSON format.
```json
{ 
    "print": "MESSAGE" 
}
```

* The consumer that will be using the LCD display is not on the same hardware platform as the 
broker and must be subscribed in the topic "test/trimble".

* The publisher can be a simple program in any programming language designed to publish the message, which will be the amount of seconds that this program has been running but only publish every 10 seconds in the topic "test/trimble".

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple example steps.

### Prerequisites

#### You will need of 2 ESP32 DevKit V1 like the image below.

<div>
  <img src="images/esp32_front.jpg" alt="Logo" width="462" height="305">
  <img src="images/esp32_back.jpg" alt="Logo" width="462" height="305">
</div>

#### The Display used is an LCD Display 16x2 with a module I2C welded

<div>
  <img src="images/display_I2C.jpg" alt="Logo" width="462" height="305">
</div>

#### Wiring for the display and the ESP32

<div class="container">
  <img style="display: inline-block;" src="images/esp32_LCD_bb.png" width="568" height="282">

  <br>

  The table below brings an overview about the wiring.

  <table>
    <tbody>
      <tr>
        <td><strong>I2C LCD</strong></td>
        <td><strong>ESP32</strong></td>
      </tr>
      <tr>
        <td><span style="font-weight: 400;">GND</span></td>
        <td><span class="rnthl rntcblack" style="font-weight: 400;">GND</span></td>
      </tr>
      <tr>
        <td><span style="font-weight: 400;">VCC</span></td>
        <td><span class="rnthl rntcred" style="font-weight: 400;">VIN</span></td>
      </tr>
      <tr>
        <td><span style="font-weight: 400;">SDA</span></td>
        <td><span class="rnthl rntcgreen" style="font-weight: 400;">GPIO 21</span></td>
      </tr>
      <tr>
        <td><span style="font-weight: 400;">SCL</span></td>
        <td><span class="rnthl rntcblue" style="font-weight: 400;">GPIO 22</span></td>
      </tr>
    </tbody>
  </table>
</div>

#### You will need VS Code installed on your machine. Follow the steps to install clicking <a href="https://code.visualstudio.com/docs/setup/setup-overview">here</a>.

#### Install PlatformIO extension for VS Code. Check the steps <a href="https://platformio.org/install">here</a>. 

#### Download and install MQTT Explorer <a href="http://mqtt-explorer.com/">here</a>. 

### Installation

_Below are the instructions to download and run the application. Please clone both in the same folder._

1. Clone the client repo
   ```sh
   git clone https://github.com/Samuel-Jonas/client-display-mqtt-esp.git
   ```
2. Clone the MQTT broker repo
   ```sh
   git clone https://github.com/Samuel-Jonas/broker-mqtt-esp.git
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage

_Follow these steps to use the project and check the feature._

1.Connect the first ESP32 into some USB port on your machine. You need a USB cable.

2.Search the port name related to your device. On Arch Linux I use this:
<br>
<br>
<img  src="images/first_USB_port.png" width="680" height="456">
<br>
<br>

3.Open **trimblecode-workspace.code-workspace** file with VS Code.
<br>
<br>
<img  src="images/open_workspace.png" width="680" height="456">
<br>
<br>

4.Open the broker-mqtt-esp project and replace the value afer '=' of monitor_port and upload_port with related to step 2 in the file **platformio.ini**.
<br>
<br>
<img  src="images/change_platform_ini.png" width="880" height="456">
<br>
<br>

5.Make sure that Switch PlatformIO Project Environment is set to broker-mqtt-esp
<br>
<br>
<img  src="images/broker_workspace.png" width="880" height="456">
<br>
<br>

6.Configure the Wifi name and password in broker-mqtt-esp/src/main.cpp
<br>
<br>
<img  src="images/wifi.png" width="880" height="456">
<br>
<br>

7.Build the project.
<br>
<br>
<img  src="images/build.png" width="880" height="456">
<br>
<br>

8.Check if the build finish successfully.
<br>
<br>
<img  src="images/sucess_build.png" width="880" height="456">
<br>
<br>

9.Now flash the firmware into the ESP32. Check in the terminal window if was uploaded successfully.
<br>
<br>
<img  src="images/flash.png" width="880" height="456">
<br>
<br>

10.See the serial monitor to get the IP address from broker.
<br>
<br>
<img  src="images/monitor.png" width="880" height="456">
<br>
<br>

>> In fact you have an MQTT broker running into ESP32.
>>
>> Once the broker was configured and still running you can continue the process to build and flash the second project called <br>client-diplay-mqtt-esp but before, we will use MQTT Explorer as the publisher program and test our broker connection.

11.Open your MQTT Explorer. Mine open this way:
<br>
<br>
<img  src="images/open_explorer.png" width="680" height="456">
<br>
<br>

12.Configure your MQTT Explorer connection to that IP address catched in step 10.
<br>
<br>
<img  src="images/connect_mqtt_explorer.png" width="880" height="456">
<br>
<br>

13.Repeat from the 1st step to the 9th step with the second ESP32. Remember that in the 5th step the name is client-display-mqtt-esp. See the result below.
<br>
<br>
<img  src="images/uploading-second-esp.png" width="880" height="456">
<br>
<br>

14.It's time to run all application. Connected both ESP32 in different USB ports to power supply them. 
<br>
<br>
<div>
<img src="images/server-foto.jpg" alt="Logo" width="462" height="305">
<img src="images/client-foto.jpg" alt="Logo" width="462" height="305">
</div>
<br>
<br>

15.Open your MQTT Explorer connected to IP address 192.168.0.5 port 1883. Choose the Topic and set the publish message below.
<br>
<br>
<img  src="images/mqtt-explorer-configure.png" width="810" height="456">
<br>
<br>

```json
{ 
    "print": "MESSAGE" 
}
```
<br>
<br>

16.Replace MESSAGE with your message, need to be maximum 16 characters to see perfecly the message in the display.
<br>
<br>
<img  src="images/publish-message.png" width="810" height="456">
<br>
<br>

17.See your display with the message.
<br>
<br>
<img  src="images/see-message.jpg" width="462" height="305">
<br>
<br>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- UNIT TESTS -->
## Unit Tests Usage
1.Check if the Switch PlatformIO Project Environment is on **client-display-mqtt-esp project**.
<br>
<br>
<img  src="images/unit-test-environment.png" width="880" height="456">
<br>
<br>

2.To run PlatformIO: Test click on the chemical baker symbol close to the trash symbol.
<br>
<br>
<img  src="images/running-tests.png" width="880" height="456">
<br>
<br>

<!-- ROADMAP -->
## Roadmap

- [x] Select a target hardware platform (e.g., Raspberry Pi, BeagleBone, etc.)
- [x] Configure it to have a mosquitto (MQTT) local broker running.
- [ ] Develop a Hardware Abstraction Layer (HAL) header file to abstract the display.
- [ ] Develop a library that implements the HAL for the selected display.
- [x] Develop a program that listen to the "/test/trimble" MQTT topic, and print the message into the display.
- [x] Develop another program that publishes the message in format "{ "print": "MESSAGE" }".
- [x] Write unit tests for your code.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Samuel Jonas - samueljonas208@gmail.com

Project Link: 
- [client-display-mqtt-esp](https://github.com/Samuel-Jonas/client-display-mqtt-esp)
- [broker-mqtt-esp](https://github.com/Samuel-Jonas/broker-mqtt-esp)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

A big thank you to the following open source libraries that significantly contributed to the completion of this project:

* [sMQTTBroker library](https://github.com/terrorsl/sMQTTBroker)
* [PlatformIO](https://platformio.org/)
* [framework-arduinoespressif32 by PlatformIO](https://registry.platformio.org/tools/platformio/framework-arduinoespressif32)
* [pubsubclient library](https://github.com/knolleary/pubsubclient)
* [LiquidCrystal_I2C library](https://github.com/johnrickman/LiquidCrystal_I2C)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/Samuel-Jonas/client-display-mqtt-esp/blob/main/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/samuel-jonas
[product-screenshot]: images/project_home.png

