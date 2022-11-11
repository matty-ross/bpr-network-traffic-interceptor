# Burnout Paradise Remastered network traffic interceptor

<img align="left" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
<img align="left" src="https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54" />
<img align="left" src="https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white" />
<img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" />

A local proxy server to intercept Burnout Paradise Remastered network traffic.


## Usage
1. Run the [main.py](https://github.com/matty-ross/bpr-network-traffic-interceptor/blob/main/src/server/main.py) script to start a local server.
2. Inject the [proxy.dll](https://github.com/matty-ross/bpr-network-traffic-interceptor/blob/main/bin/proxy.dll) into the game.
3. Wait until it connects.
4. Start monitoring the traffic using Wireshark or a similar tool.

## Compiling
A prebuild binary is available [here](https://github.com/matty-ross/bpr-network-traffic-interceptor/blob/main/bin/proxy.dll). However, you can compile the dll yourself. Just choose the x86 platform and hit compile.
