# ERD - Evolutionary RNA Designer

## Overview
ERD (Evolutionary RNA Designer) is a tool for RNA inverse folding. It is designed to find RNA sequences that fold into a given secondary structure. This project is based on evolutionary algorithms to optimize RNA sequences.

## Features
- **Inverse RNA Folding**: Finds RNA sequences that match a given secondary structure.
- **Evolutionary Algorithms**: Utilizes evolutionary strategies to optimize RNA sequences.
- **Cross-Platform**: Written in C, making it compatible with various operating systems.

## Installation
To compile and run ERD, you need a C compiler (e.g., GCC). Follow these steps to set up the project:

1. Clone the repository:
    ```sh
    git clone https://github.com/ali1366/erd.git
    cd erd
    ```

2. Compile the code:
    ```sh
    gcc -o erd main.c -lm
    ```

3. Run the executable:
    ```sh
    ./erd
    ```

## Usage
ERD is a command-line tool. After compiling, you can run the executable and follow the on-screen instructions to input the desired RNA secondary structure.
ERD can handle sequence constraints, which can be given in IUPAC
symbols using the -c option. 



ERD adapts to the new GCC compiler.

## Requierment
ERD uses the libRNA.a from the Vienna RNA Package. Thus before compiling
ERD, you have to configure and install the Vienna RNA Package. You can
download it at: 

http://www.tbi.univie.ac.at/~ivo/RNA/

Then modidy the Makefile of INFO-RNA such that the library path is set 
correctly, e.g.:

VIENNA          = /home/Vienna_1.6
## Publications
This project is based on the research presented in the following articles:

1. **[Bioinformatics, Volume 30, Issue 9, 1 May 2014, Pages 1250–1256](https://academic.oup.com/bioinformatics/article/30/9/1250/235216)**:
    - This paper discusses the methodologies and algorithms used in ERD for RNA inverse folding.

2. **[BMC Bioinformatics, Volume 15, Article number: 444 (2014)](https://bmcbioinformatics.biomedcentral.com/articles/10.1186/s12859-014-0444-5)**:
    - This article provides an in-depth analysis of the evolutionary strategies implemented in ERD.

## License
This project is licensed under the terms specified in the source code.

## Contact
For any questions or contributions, please contact the author:

- **Author**: Ali Esmaili Taheri
- **Email**: [ae.tahery[at]gmail.com]
- **Author**: Mohammad Ganjtabesh
- **Email**: [mgtabesh[at]ut.ac.ir]
## Acknowledgments
Special thanks to the contributors and the scientific community for their support and feedback.
