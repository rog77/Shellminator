@page 004_formatMatrix_page Example 004 Format Matrix

@tableofcontents

\htmlonly
<div style="display:flex; align-items: center;">
    <div style="width:100px; height:100px; margin-right: 20px;">
        <lottie-player src="Light-bulb.json" background="transparent" speed="1" style="width: 100%; height: 100%;" direction="1" playMode="normal" loop autoplay></lottie-player>
    </div>
    <div>
        <p>Most modern terminal emulators support VT100 escape sequences. These sequences are special commands that allow you to manipulate various terminal elements, such as color, style, and cursor position. If you're interested in this topic, you can find a detailed explanation <a href='https://vt100.net/docs/vt100-ug/chapter3.html'>here</a>.
        </p>
    </div>
</div>
\endhtmlonly

The demo below isn’t interactive—it simply showcases how you can format the **Serial output**.

## Live Demo

\htmlonly
<iframe id="demoFrame" src="webExamples/004_formatMatrix.html" style="height:500px;width:100%;border:none;display:block; margin-left:30px;"></iframe>
\endhtmlonly

This can be a very useful example if you want to test the capabilities of your terminal emulator. This clever little example simply tries out every combination of formatting settings so you can see what each one results in.

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

// Create a Shellminator object, and initialize it to use Serial
Shellminator shell( &Serial );

int format_table[] = {
    Shellminator::BOLD,
    Shellminator::LOW_INTENSITY,
    Shellminator::ITALIC,
    Shellminator::UNDERLINE,
    Shellminator::BLINKING,
    Shellminator::REVERSE,
    Shellminator::BACKGROUND,
    Shellminator::INVISIBLE
};

int format_table_size = sizeof( format_table ) / sizeof( format_table[ 0 ] );

const char* bold_str = "Bold";
const char* low_int_str = "Low Intensity";
const char* italic_str = "Italic";
const char* underline_str = "Underline";
const char* blink_str = "Blink";
const char* reverse_str = "Reverse";
const char* background_str = "Background";
const char* invisible_str = "Invisible";

const char* name_table[] = {
    bold_str,
    low_int_str,
    italic_str,
    underline_str,
    blink_str,
    reverse_str,
    background_str,
    invisible_str
};

int color_table[] = {
    Shellminator::BLACK,
    Shellminator::RED,
    Shellminator::GREEN,
    Shellminator::YELLOW,
    Shellminator::BLUE,
    Shellminator::MAGENTA,
    Shellminator::CYAN,
    Shellminator::WHITE 
};

int color_table_size = sizeof( color_table ) / sizeof( color_table[ 0 ] );

int background_color_table[] = {
    Shellminator::BG_BLACK,
    Shellminator::BG_RED,
    Shellminator::BG_GREEN,
    Shellminator::BG_YELLOW,
    Shellminator::BG_BLUE,
    Shellminator::BG_MAGENTA,
    Shellminator::BG_CYAN,
    Shellminator::BG_WHITE 
};

// System init section.
void setup(){

    Serial.begin(115200);

    int x;
    int y;

    // Clear the terminal
    shell.clear();
    Serial.println( "--- Style Matrix ---");
    Serial.println();

    for( y = 0; y < format_table_size; y++ ){
        for( x = 0; x < color_table_size; x++ ){
            shell.format( &Serial, color_table[ x ], format_table[ y ] );
            Serial.print( "X");
            shell.format( &Serial, Shellminator::REGULAR, Shellminator::WHITE );
        }
        Serial.print( "  " );
        Serial.println( name_table[ y ] );
    }

    Serial.println();
    Serial.println( "--- Background Matrix ---");
    Serial.println();

    for( y = 0; y < color_table_size; y++ ){
        for( x = 0; x < color_table_size; x++ ){
            shell.format( &Serial, color_table[ x ], background_color_table[ y ] );
            Serial.print( "X");
            shell.format( &Serial, Shellminator::REGULAR, Shellminator::WHITE );
        }
        Serial.println();
    }

}

// Infinite loop.
void loop(){

}
```

<div class="section_buttons">
 
| Previous          |                         Next |
|:------------------|-----------------------------:|
|[Text Formatting Example](@ref 003_textFormatting_page) | [Logo Page Example](@ref 005_logo_page) |
 
</div>