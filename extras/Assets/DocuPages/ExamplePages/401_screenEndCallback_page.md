@page 401_screenEndCallback_page Example 401 Screen End Callback

@tableofcontents

In many cases, it can be useful to trigger a **callback** when a screen session ends. Normally, after calling `beginScreen`, pressing **CTRL-C** or **Enter** will exit the GUI mode and return the system to terminal mode automatically.  

However, there are situations where detecting this exit can be helpful. For example, if the user was interacting with a **multiple-choice prompt**, it might be useful to know if they closed it instead of making a selection.  

In this example, we’ll create a **2x2 grid** containing **four buttons**. Each button, when pressed, will display a **notification** with a relevant message.  

But here’s the twist:  
- If the user **closes the grid** using **Return** or **CTRL-C**, instead of clicking a button,  
- A **notification will appear**, explaining that the grid was exited manually.  

## Live Demo

\htmlonly
<iframe id="demoFrame" src="webExamples/401_screenEndCallback.html" style="height:500px;width:100%;border:none;display:block;"></iframe>
\endhtmlonly

## Whole Code

```cpp
/*
 * Created on Aug 10 2020
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2023.05.13
*/

#include "Shellminator.hpp"
#include "Shellminator-Screen.hpp"
#include "GUI/Shellminator-ScreenGrid.hpp"
#include "GUI/Shellminator-Buttons.hpp"
#include "GUI/Shellminator-Notification.hpp"

ShellminatorButton button_1( "BTN 1" );
ShellminatorButton button_2( "BTN 2" );
ShellminatorButton button_3( "BTN 3" );
ShellminatorButton button_4( "BTN 4" );

ShellminatorNotification notification;

// Create a grid 2 rows and 2 columns
ShellminatorScreenGrid grid( 2, 2 );

// Create a Shellminator object, and initialize it to use Serial
Shellminator shell( &Serial );

Shellminator::shellEvent_t button_1_event;
Shellminator::shellEvent_t button_2_event;
Shellminator::shellEvent_t button_3_event;
Shellminator::shellEvent_t button_4_event;


void button_1_click( ShellminatorScreen* screen );
void button_2_click( ShellminatorScreen* screen );
void button_3_click( ShellminatorScreen* screen );
void button_4_click( ShellminatorScreen* screen );

void endCallback( Shellminator* parent );

// System init section.
void setup(){

    Serial.begin(115200);

    // Clear the terminal
    shell.clear();

    Serial.println( "Program Start!" );


    // Place button_1 to the first row and the first column.
    grid.addWidget( &button_1, 0, 0 );

    // Place button_2 to the first row and the second column.
    grid.addWidget( &button_2, 0, 1 );

    // Place button_3 to the second row and the first column.
    grid.addWidget( &button_3, 1, 0 );

    // Place button_3 to the second row and the second column.
    grid.addWidget( &button_4, 1, 1 );


    button_1_event.type = Shellminator::SHELL_EVENT_KEY;
    button_1_event.data = (uint8_t)'a';
    button_2_event.type = Shellminator::SHELL_EVENT_KEY;
    button_2_event.data = (uint8_t)'b';
    button_3_event.type = Shellminator::SHELL_EVENT_KEY;
    button_3_event.data = (uint8_t)'c';
    button_4_event.type = Shellminator::SHELL_EVENT_KEY;
    button_4_event.data = (uint8_t)'d';

    button_1.attachEvent( button_1_event );
    button_1.attachTriggerFunction( button_1_click );
    button_2.attachEvent( button_2_event );
    button_2.attachTriggerFunction( button_2_click );
    button_3.attachEvent( button_3_event );
    button_3.attachTriggerFunction( button_3_click );
    button_4.attachEvent( button_4_event );
    button_4.attachTriggerFunction( button_4_click );

    grid.attachEndFunction( endCallback );

    // Initialize shell object.
    shell.begin( "arnold" );

    // Register the Screen object. The terminal will pass
    // the control to it, until the user presses the ESC button.
    shell.beginScreen( &grid );

}

// Infinite loop.
void loop(){

    // Process the new data.
    shell.update();

}

void button_1_click( ShellminatorScreen* screen ){
    Shellminator* parent;
    parent = screen -> getParent();
    if( parent == NULL ){
        return;
    }
    
    notification.setText( "Button 1 pressed!" );
 
    parent -> swapScreen( &notification );
}

void button_2_click( ShellminatorScreen* screen ){
    Shellminator* parent;
    parent = screen -> getParent();
    if( parent == NULL ){
        return;
    }
    
    notification.setText( "Button 2 pressed!" );
 
    parent -> swapScreen( &notification );
}

void button_3_click( ShellminatorScreen* screen ){
    Shellminator* parent;
    parent = screen -> getParent();
    if( parent == NULL ){
        return;
    }
    
    notification.setText( "Button 3 pressed!" );
 
    parent -> swapScreen( &notification );
}

void button_4_click( ShellminatorScreen* screen ){
    Shellminator* parent;
    parent = screen -> getParent();
    if( parent == NULL ){
        return;
    }
    
    notification.setText( "Button 4 pressed!" );
 
    parent -> swapScreen( &notification );
}

void endCallback( Shellminator* parent ){
    if( parent == NULL ){
        return;
    }
    
    notification.setText( "Screen End Detected!" );

    parent -> swapScreen( &notification );
}
```

<div class="section_buttons">
 
| Previous          |                         Next |
|:------------------|-----------------------------:|
|[Simple Screen Example](@ref 400_simpleScreen_page) | [Endless Screen Example](@ref 402_endlessScreen_page) |
 
</div>