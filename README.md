

# Simple Tower Defense

This is a small game designed to showcase my UI skills. **Simple Tower Defense** is a basic tower defense game where the goal is to survive as many days as possible. The project uses **Common UI** to manage input handling across different menus and make the user interface responsive to various devices.

![Game Screenshot](https://github.com/user-attachments/assets/50fdaf70-d359-4dac-84ba-62e1fa0dc332)

## Key Features

- **Day and Night Cycle**: All game elements have both day and night colors. A single manager controls the time, and by using the Observer pattern, all relevant objects are updated accordingly.
  
- **Common UI**: The menus are made with common activatable widgets, allowing them to be easily added to an activatable stack. This enables layered widget functionality without worrying about focus management. Common UI also manages input displays, automatically showing the correct icon based on the input method.

- **Full Keyboard, Mouse, and Gamepad Support**

## Menus

### Main Menu

The main menu includes buttons for starting the game or quitting, along with a splash screen as the first screen you see.

![Main Menu Screenshot](https://github.com/user-attachments/assets/01599fd0-0323-45b5-8fbb-2a00ea0e71ea)

### End Game Menu

The End Game menu provides options to start a new game or quit, and displays your final score.

![End Game Menu Screenshot](https://github.com/user-attachments/assets/adfa38a0-3556-4bd6-95b8-352651cf5764)

## Heads-Up Display (HUD)

![HUD Screenshot](https://github.com/user-attachments/assets/5c5b037e-4ddc-4032-9b5b-a2401466b13b)

- **Pause Button**: Pauses the game and displays an exit hint if the player wishes to quit.
- **Shooting Policy Button**: Allows players to adjust the targeting behavior of the crosshair. Available modes include *Closest*, *Farthest*, *Weakest*, and *Strongest* targets.
- **Game Speed Button**: Allows players to change the game speed.
- **Health Bar**: Displays the current health visually, with exact values shown in a stats widget.
- **Lower and Upper Bars**: Anchors for the HUD widgets, enabling them to show and hide content by shifting it in and out of view.
- **Upgrades**: Three bottom buttons represent different upgrade branches to improve survivability. Upgrades cost points, which players earn by defeating enemies. Some upgrades are unlocked based on the day count, and prices increase with each purchase.
- **Crosshair**: The crosshair is a widget component in the tower that moves to targets and adjusts to target size. Multiple crosshairs can operate simultaneously.

![Crosshair Screenshot](https://github.com/user-attachments/assets/b621bcd1-f9c7-4dfb-8371-2670a972253d)
