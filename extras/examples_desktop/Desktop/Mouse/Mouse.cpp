
/*
 * Created on Aug 10 2020
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2023.05.13
 *
 * To test this example, you need a terminal emulator like PuTTY or Minicom.
 * This example shows a simple setup for Shellminator. It will create an
 * interactive interface, but it does not execute any command.
 * See Shellminator_execute example for further information.
*/


#include <stdio.h>

#include <fcntl.h>
#include <io.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>

#include "System.h"

#include "stdioStream.hpp"

#include "Shellminator.hpp"
#include "Shellminator-IO.hpp"


// Use stdio as Channel.
stdioStream stdioChannel;

// Create a Shellminator object, and initialize it to use stdioChannel
Shellminator shell( &stdioChannel );

// Create a pretty logo for the terminal.
const char logo[] =

    "   _____ __         ____          _             __            \r\n"
    "  / ___// /_  ___  / / /___ ___  (_)___  ____ _/ /_____  _____\r\n"
    "  \\__ \\/ __ \\/ _ \\/ / / __ `__ \\/ / __ \\/ __ `/ __/ __ \\/ ___/\r\n"
    " ___/ / / / /  __/ / / / / / / / / / / / /_/ / /_/ /_/ / /    \r\n"
    "/____/_/ /_/\\___/_/_/_/ /_/ /_/_/_/ /_/\\__,_/\\__/\\____/_/     \r\n"
    "\r\n"
    "Visit on GitHub: https://github.com/dani007200964/Shellminator\r\n\r\n"

;




// Main program.
int main(){

    // System init section.
    if( setlocale(LC_ALL, NULL) == NULL ){

        wprintf( L"Error setting locale!\r\n" );

    }


    // Clear the terminal
    shell.clear();

    // Attach the logo.
    shell.attachLogo( logo );

    // Initialize shell object.
    shell.begin( "arnold" );

    shell.mouseBegin();

    stdioChannel.println();
    stdioChannel.println( "Click on the screen with multiple buttons on the mouse." );
    stdioChannel.println( "The mouse wheel works as well." );



    // Infinite loop.
    while( 1 ){


        // Process the new data.
        shell.update();

        if( shell.mouseAvailable() ){

            Shellminator::mouseEvent_t mouseData = shell.mouseRead();
            stdioChannel.print("X: ");
            stdioChannel.print( mouseData.x );
            stdioChannel.print("\tY: ");
            stdioChannel.print( mouseData.y );
            stdioChannel.print( "\t" );

            switch( mouseData.event ){

                case Shellminator::MOUSE_LEFT_PRESSED:
                    stdioChannel.println( "LM P" );
                    break;

                case Shellminator::MOUSE_LEFT_RELEASED:
                    stdioChannel.println( "LM R" );
                    break;

                case Shellminator::MOUSE_RIGHT_PRESSED:
                    stdioChannel.println( "RM P" );
                    break;

                case Shellminator::MOUSE_RIGHT_RELEASED:
                    stdioChannel.println( "RM R" );
                    break;

                case Shellminator::MOUSE_MIDDLE_PRESSED:
                    stdioChannel.println( "MM P" );
                    break;

                case Shellminator::MOUSE_MIDDLE_RELEASED:
                    stdioChannel.println( "MM R" );
                    break;

                case Shellminator::MOUSE_WHEEL_UP:
                    stdioChannel.println( "MW U" );
                    break;

                case Shellminator::MOUSE_WHEEL_DOWN:
                    stdioChannel.println( "MW D" );
                    break;

                default:
                    stdioChannel.println( "INVALID" );
                    break;

            }

        }



    }

}
