# GameEngine - DX11.1 - Shadows

An improved DirectX 11.1 Game Engine from my second term assignment in Game Engine Architecture at The University of Huddersfield.

----------------------------------------------------------------------------------

This engine will focus on shaders and lighting and the way the render pipeline works. In this specific assignment I have focused mainly on the way shadows are rendered in the game world. This was for my second year.

Some of the code and HLSL files have been derived from the following tutorials. 
http://rastertek.com/tutdx11.html

Features:

- Player controller now holds camera and input.
- Omni-directional movement with mouse and keyboard.
- Input improvements (key down and key release detection.)
- Basic point light shadow shader.
- Basic direction light shadow shader.
- Blur function to perform 4 texture/shader passes to blur the shadowmap before it is rendered in the soft shadow shader.
- Soft shadow shader.
- Skybox. (NOTE: Currently using inside out sphere with increased screen cutoff as I wanted to use a texture for the skybox.)

----------------------------------------------------------------------------------

Controls:

- Camera Up: Mouse y-axis
- Camera Right: Mouse x-axis
- Forward: W
- Back: S
- Left: A
- Right: D
- Up: Space Bar
- Down: Left Ctrl
- Increase Camera Speed: Left Shift

- Light movement toggle: M
- Cube rotation toggle: R
- Show shadow map toggle: O
- Show smooth shadow: K

----------------------------------------------------------------------------------

First term game engine: https://github.com/lewisscrivens98/GameEngine-DX11-Version1
