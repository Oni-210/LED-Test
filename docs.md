This is the software side for a Protogen fursuit. It includes two LED matricies for the face as well as multiple led stripes for the body. It also includes an interface using a display in the visor and a touch sistem in the gloves.
# Architecture
WIP
# Matrix
## Matrix Class
This class is used to automatically display animations. It uses the SmartMatrix and SD libraries. It has three functions:
### run()
This function should be run in the main loop. It runs the animation. For this to properly work, avoid blocking or extremely lengthy code in the main loop.
### displayAnimation(filepath)
This function loads a new animations that starts at the next frame. filepath must lead to the .ani file of the animation.
### swapPalette(filepath)
This fuctions swaps the color palette that is displayed from the next frame onward. A palette can have up to 256 colors. If a palette is smaller, the rest will be filled with black. filepath must lead to the .pal file of the palette.
## MatrixError Enum
This class includes the different types of errors that can occur. These values are returned by the functions exept run(). Errors include:
- None: No error occured.
- WrongDimensions: The size of the animation does not match the size of the screen.
- InvalidFile: The file does not exist or is in another way unusable.
- InvalidPalette: The palette is empty, has partially entered colors or is in another way unusable.
- UnknownError: The error is unrecognized.
# File types
## .ani
Animation File. It's raw data frame after frame. Each frame is scanned row by row from left to right. One pixel is one byte. However, it does not represent a color but an index of a color palette that is currently loaded.
## .pal
Palette file. Contains up to 256 colors. One color is three bytes with one for each value in the order RGB.
# Progess
### To Do
- Create animation system for LED stripes
- Create UI
- Create expression system to unite animation, sound and LEDs 
- Include sound
- Make voice changer
### Done
- Create Matrix class for display and animation
- Write docs
- Update render to load frame contimously and unly use timer for buffer swap