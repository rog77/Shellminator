
/*
 * Created on Aug 10 2020
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2023.05.13
*/


#include "Shellminator.hpp"
#include "Shellminator-QR-Code-Module.hpp"


// Create a Shellminator object, and initialize it to use Serial
Shellminator shell( &Serial );

ShellminatorQR qrCode;




// System init section.
void setup(){

    Serial.begin(115200);

    // Clear the terminal
    shell.clear();


    Serial.println( "Shellminator webpage:" );
    Serial.println();

    // Generate a link to the Github repo.
    qrCode.generate( &Serial, "https://www.shellminator.org/html/index.html" );

    // Initialize shell object.
    shell.begin( "arnold" );


}

// Infinite loop.
void loop(){

    // Process the new data.
    shell.update();


}
