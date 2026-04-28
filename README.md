# RigBuilder Tycoon 🖥️🛠️

**Build Rigs. Crush Benchmarks. Become a Tycoon.**

RigBuilder Tycoon is an interactive PC building simulation that strictly adheres to Object-Oriented Programming (OOP) principles. Moving beyond standard console applications, this project features a fully graphical shop interface where players take customer orders, assemble PCs under strict budgets, navigate hardware bottlenecks, and overclock their builds by completing a bridged C-based Snake mini-game.

## 📖 About the Project

This game was built to demonstrate the practical application of core C++ OOP concepts, memory management, and file I/O without relying on standard template libraries.

### 🧠 Core Architecture & OOP Principles
* **Inheritance & Polymorphism:** Hardware naturally falls into a hierarchical class structure. A base `Component` class provides the blueprint (with pure virtual functions for abstraction), while specific parts (`CPU`, `GPU`, `RAM`) inherit from it to calculate their own unique performance metrics.
* **Composition:** The master `PC` class does not inherit from components; it *has* components, utilizing an array of pointers to dynamically calculate total system costs and base scores.
* **Custom Memory Management:** The project deliberately bypasses `std::vector`, utilizing a custom, memory-safe Template `Array<T>` class to handle inventory pointers.
* **Inter-Program Bridging:** The C++ Raylib interface automatically pauses, writes target score data to a text file, and executes an external C-based Snake executable (`Snake_Renewed.exe`). Once the benchmark is over, it reads the results back in real-time.
* **Data Persistence:** An independent File I/O class (`SaveSystemPlus`) tracks shop funds and high scores across multiple sessions, safely auto-saving after every transaction.

### 🎮 Game Features
* **Dynamic Economy:** Randomized customer budgets scale with the price of high-end parts. Exceeding the target benchmark score grants the player a scaled "Overclock Bonus."
* **Strict Hardware Rules:** The game actively blocks incompatible hardware combinations (e.g., attempting to slot DDR5 RAM into an older i3 motherboard).
* **Bottleneck Penalties:** Combining bleeding-edge technology (like an RTX 5090) with a low-tier CPU results in a massive mathematical penalty to the base score.
* **Penalty States:** Going over budget or failing an overclock triggers a timed "Blue Screen of Death" (BSOD) penalty, costing the player their invested funds.

---

## ⚙️ Prerequisites & Dependencies

To compile and run this project, you will need the following tools installed on your system:

1. **C++ Compiler:** MinGW-w64 (GCC) is recommended for Windows.
2. **CMake:** Version 3.10 or higher.
3. **Visual Studio Code (VS Code):** With the following extensions installed:
   * `C/C++` (by Microsoft)
   * `CMake Tools` (by Microsoft)
4. **Raylib:** The project utilizes the Raylib graphics library (which should be configured within your `CMakeLists.txt` file).

---

## 🚀 Installation & Setup

Follow these steps to download, compile, and run the game:

### 1. Download the Game
1. Click the green **`<> Code`** button at the top of this repository.
2. Select **`Download ZIP`**.
3. Extract the downloaded ZIP file to a folder on your computer.

### 2. Compile the Project
1. Open the extracted folder in **Visual Studio Code**.
2. Ensure you have the CMake Tools extension installed.
3. A prompt may appear at the bottom asking you to select a "Kit" (Compiler). Select your installed **GCC/MinGW** compiler.
4. Open the terminal in VS Code (`Terminal -> New Terminal`).
5. If you have a `build.bat` script included, simply run:
   ```bash
   ./build.bat
   ```
   *Alternatively, you can compile manually using CMake:*
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

### 3. Run the Game
Once compiled successfully, navigate to your output directory (usually the `build` or `bin` folder) and double-click the **`RigBuilderTycoon.exe`** file!

---

## 🕹️ How to Play
1. **Wait for a Customer:** A customer will appear with a randomized Budget and a Target Score.
2. **Build the Rig:** Select a CPU, GPU, and RAM from the Shop Inventory. Keep an eye on your Total Cost and Base Score.
3. **Check the Bottleneck:** Make sure your parts are compatible! If you fall short of the Target Score, the "OC Needed" indicator will tell you exactly how many points you need to grind.
4. **Run Benchmark:** Click Benchmark to open the Snake Overclocking mini-game. Eat apples to increase your score. Every apple gives you 2 performance points.
5. **Profit:** Meet the target score without going over budget to earn your base profit plus an Overclock Bonus!

---

## 🛠️ Modifying & Recompiling
If you want to edit the game logic (for example, adding new components to the arrays in `main.cpp` or tweaking the economy logic):

1. Open the necessary `.cpp` or `.h` files in VS Code and make your changes.
2. Save the files.
3. You **must recompile** the game for the changes to take effect.
4. Simply run the `build.bat` script again, or use the CMake build command:
   ```bash
   cmake --build build
   ```
5. Launch the updated `.exe` to test your changes!

---
*Developed by Faizan Talha, Muhammad Ali, and Muhammad Zain Salar.*
