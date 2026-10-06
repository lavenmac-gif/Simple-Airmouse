# Simple Air Mouse 🖱️

A small glove-based air mouse that lets you control a computer using hand and finger movements.

The idea :

Instead of holding a physical mouse, the user wears a glove containing an ESP32 and a few sensors. Different finger movements and hand gestures are interpreted as mouse actions.

This project is currently being developed and tested virtually using Wokwi before moving to the actual hardware.

https://wokwi.com/projects/475248661426141185
---

## Why I started this project

We use a mouse almost every day, but I wanted to explore what it would be like to control a computer without physically holding one.

The goal of this project is not just to make another wireless mouse. I want to understand how sensor data can be collected, interpreted as gestures, and eventually converted into actual computer commands.

I am building the project step by step, starting with a simulation and gradually moving towards a physical glove.

---

## Current Prototype

The current version is built in **Wokwi** using an ESP32 DevKit V1 and an MPU6050.

Since Wokwi does not currently provide the exact flex sensor and Hall sensor modules used in the planned physical version, potentiometers are being used to simulate their analog readings.

The current prototype includes:

- ESP32 DevKit V1
- MPU6050 accelerometer and gyroscope
- 3 potentiometers for simulating finger/sensor inputs
- Pushbutton for simulating the palm touch sensor
- Serial Monitor for observing sensor readings and detected gestures

---

## How it works

The ESP32 continuously reads data from the sensors.

The MPU6050 provides information about the movement and orientation of the hand, while the potentiometers simulate the changing values that would eventually come from the flex and Hall sensors.

The program then compares these values with predefined thresholds to determine the current gesture.

For example:

```text
Sensor Input
     ↓
ESP32 reads values
     ↓
Values are compared with thresholds
     ↓
Gesture is detected
     ↓
Gesture can later be converted
into a mouse/keyboard action
