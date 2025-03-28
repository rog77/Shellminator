
/*
 * Created on Aug 10 2020
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2023.05.13
*/


#include "Commander-API.hpp"
#include "Shellminator.hpp"
#include "Shellminator-Commander-Interface.hpp"


// We have to create an object from Commander class.
Commander commander;

bool cat_func( char *args, CommandCaller* caller );
bool dog_func( char *args, CommandCaller* caller );
bool sum_func( char *args, CommandCaller* caller );

Commander::systemCommand_t API_tree[] = {
    systemCommand( "cat", "Description for cat command.", cat_func ),
    systemCommand( "dog", "Description for dog command.", dog_func ),
    systemCommand( "sum", "This function sums two number from the argument list.", sum_func )
};

// Create a ShellminatorCommanderInterface object, and initialize it to use Serial
ShellminatorCommanderInterface shell( &Serial );




// System init section.
void setup(){

    Serial.begin(115200);

    // Clear the terminal
    shell.clear();

    commander.attachDebugChannel( &Serial );
    commander.attachTree( API_tree );
    commander.init();

    shell.attachCommander( &commander );

    // Initialize shell object.
    shell.begin( "arnold" );


}

// Infinite loop.
void loop(){

    // Process the new data.
    shell.update();


}

/// This is an example function for the cat command
bool cat_func(char *args, CommandCaller* caller ){

    caller -> print("Hello from cat function!\r\n");
    return true;

}

/// This is an example function for the dog command
bool dog_func(char *args, CommandCaller* caller ){

    caller -> print("Hello from dog function!\r\n");
    return true;

}

/// This is an example function for the sum command
bool sum_func(char *args, CommandCaller* caller ){

    // These variables will hold the value of the
    // two numbers, that has to be summed.
    int a = 0;
    int b = 0;

    // This variable will hold the result of the
    // argument parser.
    int argResult;

    // This variable will hold the sum result.
    int sum = 0;

    argResult = sscanf( args, "%d %d", &a, &b );

    // We have to check that we parsed successfully the two
    // numbers from the argument string.
    if( argResult != 2 ){

        // If we could not parse two numbers, we have an argument problem.
        // We print out the problem to the response channel.
        caller -> print( "Argument error! Two numbers required, separated with a blank space.\r\n" );

        // Sadly we have to stop the command execution and return.
        return false;

    }

    // Calculate the sum.
    sum = a + b;

    // Print out the result.
    caller -> print( a );
    caller -> print( " + " );
    caller -> print( b );
    caller -> print( " = " );
    caller -> println( sum );
    return true;
}