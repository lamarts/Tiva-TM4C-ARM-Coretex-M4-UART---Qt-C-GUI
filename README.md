# Tiva-TM4C-ARM-Coretex-M4-UART---Qt-C-GUI

This repository contains the main program (TivaUARTmain.c) for the Tiva C launchpad to communicate over UART to a PC or Mac.  The PC or Mac must use the same settings, such as baud rate, data bits, stop bit, flow control, etc as the launchpad.

The demonstration assumes one has knowledge of the Tiva C launchpad, GPIO, UART functions and how to program the launchpad.

In addition the repository contains the files for the Qt project that is required for the Serial Communications to work from the GUI.

//////  For Windows...the COMM Port can be found by connecting the launchpad to the USB port on the computer.   This will be used in the Qt Serial Port class member definitions when using Windows for Qt implementation.

/////   For Mac...the COMM Port can be found by identifying the vendor id and product id from the launchpad.   This will be used in the Qt Serial Port class member definitions when using Mac for Qt implementation.

The Qt project should have the following folders and files

QtSerialCommunications -> QtSerialCommunications.pro
in Headers folder -> mainwindows.h
in Source folder -> main.cpp, mainwindow.cpp
in Forms -> mainwindow.ui

In the form, simply create the 4 buttons in the ui to match the code in the TivaUARTmain.c program and use the code in the folders.

