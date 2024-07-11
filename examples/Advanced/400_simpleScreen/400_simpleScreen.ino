
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


#include "Shellminator.hpp"
#include "Shellminator-Screen.hpp"
#include "GUI/Shellminator-Buttons.hpp"
#include "GUI/Shellminator-Notification.hpp"



// Create a Shellminator object, and initialize it to use Serial
Shellminator shell( &Serial );

ShellminatorNotification notification;

// Create a class named layout. This is inherited from the ShellminatorScreen class,
// this way it can be added to the terminal as a screen.
class myLayout : public ShellminatorScreen{

public:

    // Override the base draw function with our custom one.
    void draw() override;

    // Override the base init function with our custom on e.
    void init( Shellminator* parent_p, Stream* channel_p ) override;

    void update( int width_p, int  height_p ) override;

private:

    // Create the two ShellminatorPlot object. We will use them side by side in out layout.
    ShellminatorButton buttonLeft;
    ShellminatorButton buttonRight;

    Shellminator::shellEvent_t leftButtonEvent;
    Shellminator::shellEvent_t rightButtonEvent;

    bool redraw = true;

};

void myLayout::update( int width_p, int  height_p ){
    Shellminator::shellEvent_t newEvent;

    // Size of the left plot.
    int widthLeft;
    int heightLeft;

    // Origin of the left plot.
    int originLeftX;
    int originLeftY;

    // Size of the right plot.
    int widthRight;
    int heightRight;

    // Origin of the right plot.
    int originRightX;
    int originRightY;


    if( parent == NULL ){
        return;
    }

    width = width_p;
    height = height_p;

    // The left plot will be on the left side...
    originLeftX = 1;
    originLeftY = 1;

    widthLeft = width / 2;
    heightLeft = height;

    // The left plot will be on the right side...
    originRightX = width / 2 + 1;
    originRightY = 1;

    widthRight = width - originRightX;
    heightRight = height;

    // Set the calculated origins to the two plots.    
    buttonLeft.setOrigin( originLeftX, originLeftY );
    buttonRight.setOrigin( originRightX, originRightY );

    // IMPORTANT! We have to draw from left to right and from up to down.
    // For this reason we start the drawing with the left plot.
    buttonLeft.update( widthLeft, heightLeft );

    // Draw the right plot secondly.
    buttonRight.update( widthRight, heightRight );

    newEvent = parent -> readEvent();

    // In case of empty event, we can't do anything.
    if( newEvent.type == Shellminator::SHELL_EVENT_EMPTY ){
        return;
    }

    if( newEvent.type == Shellminator::SHELL_EVENT_RESIZE ){
        redraw = true;
        return;
    }

}

void myLayout::draw(){

    // Only draw if resized event or timer event happened.
    if( !redraw ){
        return;
    }
    redraw = false;

    // IMPORTANT! We have to draw from left to right and from up to down.
    // For this reason we start the drawing with the left plot.
    buttonLeft.draw();

    // Draw the right plot secondly.
    buttonRight.draw();

}

void leftButtonClick( ShellminatorScreen* screen ){
    Shellminator* parent;
    parent = screen -> getParent();
    if( parent == NULL ){
        return;
    }
    notification.setText( "Hurray!\nYou pressed the left button!" );
    parent -> swapScreen( &notification );
}

void rightButtonClick( ShellminatorScreen* screen ){
    Shellminator* parent;
    parent = screen -> getParent();
    if( parent == NULL ){
        return;
    }
    notification.setText( "Hurray!\nYou pressed the right button!" );
    parent -> swapScreen( &notification );    
}

void myLayout::init( Shellminator* parent_p, Stream* channel_p ){

    parent = parent_p;
    channel = channel_p;

    // Construct the two plot objects.
    buttonLeft = ShellminatorButton( "Left" );
    buttonRight = ShellminatorButton( "Right" );

    buttonLeft.attachTriggerFunction( leftButtonClick );
    buttonRight.attachTriggerFunction( rightButtonClick );

    leftButtonEvent.type = Shellminator::SHELL_EVENT_KEY;
    leftButtonEvent.data = (uint8_t)'l';

    rightButtonEvent.type = Shellminator::SHELL_EVENT_KEY;
    rightButtonEvent.data = (uint8_t)'r';

    buttonLeft.attachEvent( leftButtonEvent );
    buttonRight.attachEvent( rightButtonEvent );

    buttonLeft.setColor( Shellminator::YELLOW );
    buttonRight.setColor( Shellminator::BLUE );

    // Initialise the plot objects.
    buttonLeft.init( parent, parent -> channel );
    buttonRight.init( parent, parent -> channel );

}

// Create an object from the layout class.
myLayout splitLayout;




// System init section.
void setup(){

    Serial.begin(115200);

    // Clear the terminal
    shell.clear();

    Serial.println( "Program Start!" );

    // Initialize shell object.
    shell.begin( "arnold" );

    // Register the Screen object. The terminal will pass
    // the control to it, until the user presses the ESC button.
    shell.beginScreen( &splitLayout );


}

// Infinite loop.
void loop(){

    // Process the new data.
    shell.update();


}
