Simple Tower defense.

This is a small game to show my UI skills. Basically is a very basic tower defense where the goal is to survive for as many days as you can. For this project I used Common UI as base for the user interface to manage inputs and to make easier working with different menus.

![STD_1](https://github.com/user-attachments/assets/50fdaf70-d359-4dac-84ba-62e1fa0dc332)

Key features:

- Day and night cycle: All the elements in the game have associated two colors, one for the day and other night. The way I made this possible is by having a single manger that controlls the time and by using the Observer patter It is communicated to all the other objects.
- Common ui: the menus are all common actibable widgets which allows me to add the to a common activable stack so I can add layers of activable widgets with out having to worry about which one has the focus. Common ui, also allows me to represent in a much better way the inputs in the the UI with the common action widgets which control which input method is being used and consecuently shows the correct icon.
- Full keyboard , mouse and gamepad support.

Menus
- Main menu: it is formed by the buttons that take you either to the quit to menu screen or to the game level and by a splash screen. this screen is the first thing you see before accesing to the buttons.

![STD_2](https://github.com/user-attachments/assets/01599fd0-0323-45b5-8fbb-2a00ea0e71ea)

- End Game menu: the end game menu basically is a way to end a game and start another or just stop playing, it also tells you your score.

![STD_3](https://github.com/user-attachments/assets/adfa38a0-3556-4bd6-95b8-352651cf5764)

Hud:

![STD_4](https://github.com/user-attachments/assets/5c5b037e-4ddc-4032-9b5b-a2401466b13b)
- Pause Button: allows you to pause the game to take a moment to think. it can also be triggered using inputs. when the game is paused the exit hint apears in case the player wants to quit.
- Shotting policy button: allows you to change the way the crosshair targets the enemies, the availible shooting policies are closest,farthest,weakest and strongest.
- game speed button: allows the player to change the speed of the game.
- Health bar: shows the current health in a visual way, in the stat widget you can see the actual values.
- Lower and upper bars: all the widgets are anchored to this bars, so they can show and hide the content by moving it away.
- Upgrades: the three bottom buttons indicate the upgrade branches, this are upgrades that make you survive longer. this upgrades uses points as currency which you get when you kill an enemy. on the other hand this upgrades are locked per days, meaning that some upgrades wont be availible until a certain day. finally this upgrades cost incrementally so each time will be a bit more spensive.
- cross hair: the cross hair actually is not in the hud but it is a widget component in the tower. this crosshairs move to their target and adapt to its size. You can also have multiple crosshairs which will work simultanouslly.
![STD_5](https://github.com/user-attachments/assets/b621bcd1-f9c7-4dfb-8371-2670a972253d)
