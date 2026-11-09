# Breakout Game

A classic 2D Breakout clone built in modern C++ (C++17) utilizing the **Raylib** multimedia framework and structured with **CMake** for clean, cross-platform building.

## 🚀 Features

- **Smooth Paddle Physics:** Direct paddle management using standard keyboard configuration controls.
- **Dynamic Grid Matrix Layout:** Automated row-generation palette with customizable sizing, scaling, and safe margin offsets.
- **Diverse Brick Categories:**
  - 🟥 **Standard Bricks:** Regular colored breakable elements.
  - 🟢 **Ball Power-ups:** Breaks to duplicate active balls up to a maximum of 3 concurrent entities.
  - 🟦 **Expand Power-ups:** Increases paddle horizontal dimensions temporarily for 5 seconds.
  - 💠 **Solid Indestructible Bricks:** Structural obstacles highlighted in custom aqua-blue overlays that redirect trajectory but remain unbroken.
- **Smart Win-States:** Integrated logic scans levels using `std::none_of` algorithms to transition phases cleanly when all breakable pieces are cleared.
---

<img width="1026" height="800" alt="Recording 2026-11-09 181718" src="https://github.com/user-attachments/assets/4f0e27f2-a64b-409d-9fde-4df4ae8acceb" />

---

## 🎮 How to Play
- **Launch Game:** Press the `UP ARROW` key on the splash screen to generate the field and launch the primary ball tracking state.
- **Movement:** Use horizontal navigational inputs to position the paddle under descending ball trajectories.
- **Objective:** Deflect vectors upward to target breakable structures while avoiding bottom border boundaries. Avoid traps and clear elements to unlock higher high-scores!

---

## 🛠️ Prerequisites & Dependencies

To compile and launch the codebase, ensure your local system environment includes:
- **C++17 Compiler:** GCC, Clang, or MSVC (Visual Studio 2019+ recommended).
- **CMake:** Version 3.13 or newer.
- **Raylib:** Built-in via subdirectory cloning (`thirdParty/raylib-6.2`).

---

## 💻 Building the Project

### Using Visual Studio (CMake Folder Mode)
1. Open Visual Studio.
2. Select **File** -> **Open** -> **Folder...** and select this directory.
3. Wait for the bottom status bar to read `CMake generation finished`.
4. In the top middle toolbar target dropdown selector (next to the green Play button), switch the target profile option from `ALL_BUILD` or `ZERO_CHECK` to **`Breakout.exe`**.
5. Press **F5** to start compilation and launch debugging.

### Using Command Line Interface (CLI)
Navigate to your project root folder and execute the following commands:

```bash
# 1. Create a dedicated compiler sandbox directory
mkdir build && cd build

# 2. Configure project cache generation
cmake ..

# 3. Compile the executable binaries
cmake --build .

# 4. Execute the binary output
./Breakout
```
