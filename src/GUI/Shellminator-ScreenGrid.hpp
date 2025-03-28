/*
 * Created on June 23 2024
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2024.06.23
*/

/*
MIT License

Copyright (c) 2023 Daniel Hajnal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef SHELLMINATOR_SCREEN_GRID_HPP_
#define SHELLMINATOR_SCREEN_GRID_HPP_

    #ifdef ARDUINO
        #include "Arduino.h"
    #else
        #include "System.h"
    #endif

    #include "Stream.h"

    #include "Shellminator.hpp"
    #include "Shellminator-Screen.hpp"
    #include "Shellminator-Helpers.hpp"

    #include <stdio.h>
    #include <stdint.h>
    #include <string.h>


    class ShellminatorScreenGrid : public ShellminatorScreen{

    public:

        /// Empty constructor.
        ShellminatorScreenGrid();

        ShellminatorScreenGrid( int numOfRows_p, int numOfColumns_p );

        /// Init function.
        ///
        /// This function is called by the host terminal, when the plot object gets registered to it.
        /// You can put all the initialisation section here.
        /// @param parent_p Pointer to the caller terminal object.
        /// @param channel_p This is a pointer to a Stream object, which can be used to print the output
        ///                  data.
        /// @note Please use the `channel_p` object instead of `parent -> channel` method.
        ///       This object can be a regular channel __or a buffer accelerated one.__
        ///       The logic behind the buffering and flushing is handled by the caller terminal.
        void init( Shellminator* parent_p, Stream* channel_p ) override;

        /// Draw function.
        ///
        /// This function is called by the caller terminal if redraw
        /// is requested. If you need to draw your screen, the 
        /// requestRedraw function must be called on the parent terminal
        /// object. The reason for this is to save some CPU time and do
        /// not waste it to draw something unnecessarily.
        void draw( bool noClear = false ) override;
        
        /// Update function.
        ///
        /// The update function must be used to process events and not to
        /// draw the objects. It is called much frequently than, the draw
        /// function. All the event handling should be done in the update
        /// function, including key and mouse detection along with various
        /// events.
        /// @param width_p The width of the screen area in characters.
        /// @param height_p The height of the screen area in characters.
        void update( int width_p, int  height_p ) override;

        void forceRedraw() override;

        void addWidget( ShellminatorScreen* widget, int row, int column, int rowSpan = 1, int columnSpan = 1 );

    protected:

        /// This flag shows that redraw is necessary. In this
        /// implementation redraw is only required when the
        /// screen is resized.
        bool redraw = true;

        int numOfRows = 0;
        int numOfColumns = 0;

        int cellWidth = 0;
        int cellHeight = 0;

        ShellminatorScreen* head = NULL;

    };

#endif