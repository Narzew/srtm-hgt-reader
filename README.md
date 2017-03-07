# Elevations Reader
Software to easily check all elevations from a file and save output to other file.
    Supports up to 10000 coordinates per file.
    Support 3 arc second files.
## Usage
    ElevationsReader.exe inputfile outputfile
    input file structure:
    x1 y1 d1
    x2 y2 d2
    x3 y3 d3
    output file structure:
    x1 y1 d1 e1
    x2 y2 d2 e2
    x3 y3 d3 e3
    x - latitude (decimal)
    y - longitude (decimal)
    d - distance (put what you want here, but it has to be a float or integer); program will left this in place; I prefer using this as reference how much distance is between actual and first coordinate.
    Put .hgt files in the srtm folder!
## Version log:
    1.1 - Fixed negative coords bug, added distance field.
    1.01 - Calculations are now more precise
    1.0 - Initial release.
    Forked from zbycz repository and added command-line functionality.
## Copyrights
Elevations Reader © zbycz & Narzew
    Build upon SRTM-HGT-Reader by zbycz
    https://github.com/zbycz/srtm-hgt-reader
    Command line funcionality added by Narzew
    https://github.com/narzew/
