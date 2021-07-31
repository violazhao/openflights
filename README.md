# Viola Zhao

# OpenFlights Dijkstra's Algorithm

The purpose of this program is to find the shortest airplane paths between two cities, possibly with a stop in between. The routes database I used is from https://openflights.org/data.html. Instead of
using all of the data however, I decided to use a smaller sample. By using an accurate smaller sample size, I am assuming this implementation will work with all cities. This project is very useful in the real world, as airlines can easily find the shortest path possible between two cites.

## Dependencies

Utilizes Dijkstra's Algorithm (BFS), OpenFlights routes database, C++, VSCode

## Usage

Once the project is downloaded, add your routes dataset into the project folder (your dataset must be a text file formatted like the OpenFlights dataset, or you can just use the OpenFlights one.)

On main.cpp, line 11, change the file path to your data file. Then, run `make` in the project folder on the command line to build the project.

Running `./finalproj` will prompt you to input whether you would like to run shortest path or landmark path
- Shortest path will give you the shortest path between two airports
- Landmark path will give you the shortest path between two airports with a stop in the middle at a
particular airport

Please input either `shortest path` or `landmark path`

Next, the program will prompt you to input source, destination, and if you are running landmark path, stop airports. Please input the IATA 3-letter codes for the airports you would like to use.

Once these are all inputted, the program will run and output put the particular sequence of airports your flight will take or notify you that no route between the airports you inputted is possible.

## Tests

To run the tests, you can `make test` and `./test`.
