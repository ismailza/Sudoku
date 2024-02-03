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

  ![image](https://github.com/ismailza/Sudoku/assets/122171824/a83349d0-f001-4932-84b2-d33456ba9454)

  ![image](https://github.com/ismailza/Sudoku/assets/122171824/82ab7d47-bcce-4ec2-b1d0-0eacdc403be7)

  ![image](https://github.com/ismailza/Sudoku/assets/122171824/7b6de459-3ce7-446e-ae2d-a1d8b033f054)

  ![image](https://github.com/ismailza/Sudoku/assets/122171824/b5997af8-8156-4099-a793-e5bacf0586ce)

  ![image](https://github.com/ismailza/Sudoku/assets/122171824/770b4845-2616-4a46-bb2b-cecd1db92035)

  ![image](https://github.com/ismailza/Sudoku/assets/122171824/c5c5f7b8-83b1-4c3c-ab6e-fe6620e954f8)

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
