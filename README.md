![Logo](./images/Logo.png)

<details>
	<summary>Table of contents</summary>
	<ol>
		<li>
			<a href = "#about-the-project">About the project</a>
		</li>
		<li>
			<a href = "#technologies-used">Technologies used</a>
		</li>
		<li>
			<a href = "#getting-started">Getting started</a>
			<ul>
				<!-- <li>
					<a href = "#released-project">Released project</a> -->
				</li>
				<li>
					<a href = "#compiling-from-source">Compiling from source</a>
				</li>
			</ul>
		</li>
		<li>
			<a href="#license">License</a>
		</li>
		<li>
			<a href="#contact-us">Contact us</a>
		</li>
		<li>
			<a href="#acknowledgements">Acknowledgements</a>
		</li>
	</ol>
</details>

## About the project

This is the event manager made by team Somnum for the sprint "Linked list". It consists of a console utility made in ncurses/PDcurses

## Technologies used

We used two main technologies:

- C++
- ncurses / [PDcurses](https://github.com/wmcbrine/PDCurses)
- [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser) by [ben-strasser](https://github.com/ben-strasser)
- [utest.h](https://github.com/sheredom/utest.h) by [Sheredom](https://github.com/sheredom)

## Getting started

This section contains information about how to get the project up and running on your system

#### Compiling from source

##### Prerequisites

- If you are using a Windows machine it is recommended you have the `make` command and a compiler(Preferably `g++`). The recommended compiler is [MSYS2](https://www.msys2.org/)
- If you are on Linux download `ncurses.h`
  - Arch and Arch-based distros
  ```sh
  pacman -S ncurses
  ```
  - Debian and Debian-based
  ```sh
  apt-get install libncurses5-dev libncursesw5-dev
  ```

##### Compiling and running

1. Clone the project

```sh
git clone https://github.com/RMPapazov19/Somnum-Project
```

2. Choose the right makefile
   - If you are using Windows
   ```sh
   mingw32-make -f Windows
   ```
   - If you are using Linux
   ```sh
   make -f Linux
   ```
1. Run the project
   - Windows
   ```cmd
   cd bin/
   main.exe
   ```
   - Linux
   ```sh
   ./bin/main.out
   ```

## License

This project is licensed under the MIT license. See [License](License) for more information.

## Contact us

Presian Stefanov

- Github - [@PSStefanov19](https://github.com/PSStefanov19)
- Instagram - [@presian.cpp](https://www.instagram.com/presian.cpp/)

## Acknowledgements

Helpful resources I found while working on the project:

- [Choose an Open Source License](https://choosealicense.com/)
- [Colsby Computer Science's makefile guide](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)
- [TLDP's Ncurses HOWTO](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/)
- [PDcurses](https://github.com/wmcbrine/PDCurses)
- [@AEManov20](https://github.com/AEManov20) for giving me the idea of using .csv files
