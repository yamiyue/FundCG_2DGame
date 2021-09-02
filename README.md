
# FundCG_2DGame
NTUST Fundamental of Computer Graphics Project 2

## Introduction
The propose of this project is to use the Opengl texture arrays to make 2D animations. In the same time, use these animations to make a 2D Game.

## Goal of the game
Control the character to destroy the boxes and collect the apples. 

## Implement

### Platform/Environment
- QT 5.14.1
- MSVC2017
- OpenGL 4.3
- Windows10 64bit

### Charcter
Character in Maple Story 

#### Actions
- Idle
- Walk
- Jump
- Attack
 
Use 4 sets continous images of the character actions. Press left/right arrow keys to control character to walk left/right. Press alt key to make character jump. Press ctrl key to let character attack. Press Z key to pick up apples.
#### Physics
- Terrain Collision
- Gravity

Use brute force to deal with collision problem. Set the postion constrains and check whether the collision occur to stop character.

Set simple gravity(no acceleration) for character to achieve falling action.
### MiniMap
Render the scene in framebuffer and bind as a texture. Finally, render the texture on screen. 

http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
### Shaders

- CRT effect

https://www.shadertoy.com/view/ldjGzV
- Snow effect

https://www.shadertoy.com/view/ldsGDn
- Mosaic effect

https://www.shadertoy.com/view/4d2SWy
- Shake effect

https://www.shadertoy.com/view/XdcBzs

## Game Demo

https://youtu.be/6u_z9dkebKk

![P2](https://user-images.githubusercontent.com/36958393/131788663-c379fef0-0734-468e-bf16-bde97521f5e9.jpg)

## Texture source

- Character

https://maplestory.net/design#
- Box

https://maplestory.net/design#
- BackGround

MapleStory
- Apple

MapleStory
- Content in TV 

MapleStory
- Tv

MapleStory
- Finish

MapleStory
