# Breakout Game

A classic 2D Breakout clone built in C++ using Raylib and CMake.

## 🚀 Features

- **Smooth Paddle Physics:** Direct paddle management using standard keyboard configuration controls.
- **Dynamic Grid Layout:** Automated row-generation palette with customizable sizing, scaling, and margin offsets.
- **Diverse Brick Categories:**
  - 🟥 **Standard Bricks:** Regular colored breakable elements.
  - 🟢 **Ball Power-ups:** Breaks to duplicate active balls up to a maximum of 3 balls.
  - 🟦 **Expand Power-ups:** Increases paddle width temporarily for 5 seconds.
  - 💠 **Solid Indestructible Bricks:** Structural obstacles highlighted in aqua-blue that redirect trajectory but remain unbroken.
- **Smart Win-States:** Using `std::none_of` to check if the player has won by taking in account the indestructible Bricks that cannot be broken.

<img width="1026" height="800" alt="Recording 2026-11-09 181718" src="https://github.com/user-attachments/assets/4f0e27f2-a64b-409d-9fde-4df4ae8acceb" />

---

## 🎮 How to Play
- **Launch Game:** Press the `UP ARROW` key on the splash screen to generate the field and launch the primary ball tracking state.
- **Movement:** Use horizontal navigational inputs to position the paddle under descending ball trajectories.
- **Objective:** Deflect vectors upward to target breakable structures while avoiding bottom border boundaries. 
