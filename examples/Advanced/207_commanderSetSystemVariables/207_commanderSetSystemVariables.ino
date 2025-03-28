
/*
 * Created on Aug 10 2020
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2023.05.13
*/


#include "Commander-API.hpp"
#include "Commander-Arguments.hpp"
#include "Shellminator.hpp"
#include "Shellminator-Commander-Interface.hpp"


// We have to create an object from Commander class.
Commander commander;

bool echo_func( char *args, CommandCaller* caller );
bool export_func( char *args, CommandCaller* caller );

Commander::systemCommand_t API_tree[] = {
    systemCommand( "echo", "Simple echo command.", echo_func ),
    systemCommand( "export", "Simple export command: [TARGET][VALUE]", export_func )
};

// These will be the system variables.
char* VERSION = (char*)"V1.0.2a";
int SPEED = 0;
float AREA = 1.41;

// Create system variable tree.
Commander::systemVariable_t System_variables[] = {
    systemVariableString( VERSION ),
    systemVariableInt( SPEED ),
    systemVariableFloat( AREA )
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

    // Attach system variables to the commander object.
    commander.attachVariables( System_variables );

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

bool echo_func(char *args, CommandCaller* caller ){
    char textBuffer[ 30 ];

    // The text argument is required to parse system variables.
    Argument text( args, 0 );

    // Try to parse string or system variables
    if( text.parseString( textBuffer ) ){
        caller -> println( textBuffer );
        return true;
    }

    // If parsing failes, just print out the args.
    caller -> println( args );
    return true;
}

bool export_func(char *args, CommandCaller* caller ){
    // The first argument will be the system variable itself.
    Argument variable_object( args, 0 );
    // The second argument will be the new value for the system variable.
    Argument variable_value( args, 1 );

    // This will hold the reference of the system variable (if it can be found).
    Commander::systemVariable_t* variable;

    // The parser will try to interpret the data as a system variable first.
    variable_object.parseFloat();

    // Parse the new value as a float (can be cast back to int if needed).
    variable_value.parseFloat();

    // Try to extract the reference of a system variable.
    // If it is found, `variable` will not be NULL.
    variable = variable_object.getSystemVariable();

    // Check if the first argument is a system variable.
    if( variable != NULL ){

        // Check if the found system variable is a string.
        if( variable -> data.type == Commander::VARIABLE_STRING ){
            caller -> println( "String variable can not be modified!" );
            return false;
        }

        // Check if the new value cannot be parsed.
        if( !(bool)variable_value ){
            caller -> println( "Variable needs a new value!" );
            return false;
        }

        if( variable -> data.type == Commander::VARIABLE_FLOAT ){
            // Assign the float value to the system variable.
            *( variable -> data.data.floatData ) = (float)variable_value;
            return true;
        }

        // Assign integer value by converting float to int.
        *( variable -> data.data.intData ) = (int)( (float)variable_value );
        return true;

    }

    // We are here, because the first argument was not a system variable.
    caller -> println( "Variable not found!" );
    return false;
}