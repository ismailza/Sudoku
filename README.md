# Sudoku

Welcome to the Sudoku Game repository! This project is a classic Sudoku puzzle game built using [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org/). Enjoy a user-friendly interface, various difficulty levels, and hours of brain-teasing fun!

## Features

- Classic Sudoku gameplay with a clean, intuitive interface.
- Multiple difficulty levels to challenge both beginners and seasoned players.
- Enhanced audio effects for an immersive experience.
- Save and resume game functionality.

## Screenshots

<p align="center">

  ![image](https://github.com/ismailza/Sudoku/assets/122171824/6fcb3e99-c5c8-49d4-b1b0-573eb3128635)
</p>
<p align="center">

  ![image](https://github.com/ismailza/Sudoku/assets/122171824/a83349d0-f001-4932-84b2-d33456ba9454)
</p>
<p align="center">

![image](https://github.com/ismailza/Sudoku/assets/122171824/5f5fafbd-1e7a-4e71-b850-f24cf57c4665)
</p>
<p align="center">

![image](https://github.com/ismailza/Sudoku/assets/122171824/4484c161-5381-4eeb-8095-c553117d420e)
</p>

<p align="center">

![image](https://github.com/ismailza/Sudoku/assets/122171824/7846ad45-b1ce-4438-83a5-20a240971b32)
</p>

## Getting Started

### Prerequisites

Ensure you have the following installed on your system:

- A C++ compiler (GCC, Clang, MSVC, etc.)
- [SFML 2.6.1](https://www.sfml-dev.org/download/sfml/2.6.1/)

`Note`: 
- If you are using Visual Studio Code, you need to add the SFML include path to your project's `c_cpp_properties.json` file. For example:

  Navigate to .vscode/c_cpp_properties.json and add the following to the includePath array in the configurations object:

  ```json
  {
    "configurations": [
      {
        "includePath": [
          "/your/path/to/SFML-2.6.1/include"
        ],
      }
    ]
  }
  ```

- Change the Makefile to reflect the location of your SFML include and lib directories. For example:
  
    ```makefile
    # SFML include and lib directories
    SFML_INCLUDE = "\your\path\to\SFML-2.6.1\include"
    SFML_LIB = "\your\path\to\SFML-2.6.1\lib"
    ```

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/ismailza/Sudoku.git
    ```

2. Navigate to the project directory:
   ```bash
   cd Sudoku
   ```

3. Compile the project (ensure SFML is correctly set up):
   ```bash
    make
    ```

4. Run the executable:
    ```bash
    make run
    ```

## Contributing

Contributions are what make the open-source community such an amazing place to be, learn, inspire, and create. Any contributions you make are greatly appreciated.

1. Fork the Project
2. Create your Feature Branch (git checkout -b feature/feature_name)
3. Commit your Changes (git commit -m 'Add some feature_name')
4. Push to the Branch (git push origin feature/feature_name)
5. Open a Pull Request

## License

Distributed under the MIT License. See `LICENSE` for more information.
