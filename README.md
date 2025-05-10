♻️ Smart Disposal Machine - Green Guardian

Welcome to the repository of Green Guardian, a Smart Disposal Machine built to modernize and automate waste management. Designed with a combination of AI, IoT, and mechanical engineering, this system aims to reduce human intervention, improve hygiene, and enable intelligent waste segregation.

🚀 Project Overview

The Smart Disposal Machine (SDM) is an innovative solution for waste handling that automatically:

Detects waste using a USB camera

Classifies it using AI (Gemini 1.5)

Compresses it with a lead screw mechanism

Sorts it into the appropriate category (biodegradable, recyclable, or non-recyclable)

Monitors fill levels and notifies users in real-time via a web dashboard

It is ideal for use in schools, campuses, offices, and smart cities, offering contactless interaction, increased efficiency, and scalable infrastructure for sustainable waste management.

🧠 Key Features

✅ AI-Powered Waste ClassificationUtilizes Google Gemini 1.5 to categorize waste into proper compartments.

📆 Automated CompressionReduces volume using a lead screw and NEMA17 stepper motor for extended storage capacity.

📡 IoT MonitoringUltrasonic sensors track bin levels in real-time and update a web dashboard (Streamlit).

🧬 Hygienic OperationTouchless lid operation with IR sensors and servos minimizes contamination risk.

🗌 Web DashboardReal-time status with color indicators and bin location mapping. Includes unique bin IDs and notification alerts.

🛠️ Technical Stack

Component

Description

AI Model

Gemini 1.5 (Google)

Microcontrollers

Raspberry Pi 4, Arduino Uno

Sensors

Ultrasonic, IR Proximity

Motors

SG90 Servo, MG995 Servo, NEMA17 Stepper

Mechanism

Lead Screw Compression + Flap-based Redirection

Software

Python, Streamlit Dashboard

Communication

USB Camera, IoT-based Monitoring

🔮 Future Enhancements

Integration with smart city waste routing systems

Detection of hazardous and electronic waste

Full automation of waste pickup via robotics

More efficient deep-learning classification models
