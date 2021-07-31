# Viola Zhao

# OpenFlights Dijkstra's Algorithm

Program finds the shortest airplane paths between two cities, possibly with a stop in between. 

## Dependencies

Utilizes Dijkstra's Algorithm (BFS), OpenFlights routes database (https://openflights.org/data.html), C++, VSCode

## Usage

Add your routes dataset into the project folder (must be a text file formatted like the OpenFlights dataset), or use the default OpenFlights routes dataset.

- If you use your own routes dataset, change the file path to your data file on main.cpp, line 11.

Run `make` in the project folder on the command line to build the project.

Running `./finalproj` will prompt you to input whether you would like to run shortest path or landmark path
- Shortest path will give you the shortest path between two airports
- Landmark path will give you the shortest path between two airports with a stop in the middle at a
particular airport

Please input either `shortest path` or `landmark path`

Next, the program will prompt you to input source, destination, and if you are running landmark path, stop airports. Please input the IATA 3-letter codes for the airports you would like to use.

Program will run and output the shortest airplane path your flight will take, or notify you that no route between the airports you inputted is possible.

## Tests

To run the tests, you can `make test` and `./test`.
