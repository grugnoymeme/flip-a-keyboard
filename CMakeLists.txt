<?xml version="1.0" encoding="UTF-8"?>
<application>
    <name>Flip-A-Keyboard</name>
    <author>Your Name</author>
    <description>A Flipper Zero application to monitor keyboard input via Bluetooth and USB.</description>
    <category>Utility</category>
    <version>1.0.0</version>
    <build>
        <type>native</type>
        <source_dir>src</source_dir>
        <output>Flip-A-Keyboard.fap</output>
        <toolchain>arm-none-eabi-gcc</toolchain>
        <platform>flipper</platform>
    </build>
    <dependencies>
        <dependency>furi</dependency>
    </dependencies>
    <icon>icon.png</icon>
</application>
