# Tiva-TM4C-ARM-Coretex-M4-UART---Qt-C-GUI

This repository contains the main program (TivaUARTmain.c) for the Tiva C launchpad to communicate over UART to a PC or Mac.  The PC or Mac must use the same settings, such as baud rate, data bits, flow control, etc as the launchpad.

The demonstration assumes one has knowledge of the Tiva C launchpad, GPIO, UART functions and how to program the launchpad.

In addition the repository contains the files for the Qt project that is required for the Serial Communications to work from the GUI.

The Qt GUI program uses the vendor id and product id from the launchpad to obtain the USB information in which to communicate with the launchpad and utilizes this information as part of the serial communication settings in the Qt program.

The Qt project should have the following folders and files

QtSerialCommunications -> QtSerialCommunications.pro
in Headers folder -> mainwindows.h
in Source folder -> main.cpp, mainwindow.cpp
in Forms -> mainwindow.ui

In the form, simply create the 4 buttons in the ui to match the code in the TivaUARTmain.c program and use the code in the folders.

