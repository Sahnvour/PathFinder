#Examples

I wrote some examples to illustrate how to use/integrate PathFinder for solving problems that involve path planning. They may not be the best way to do some specific C++ coding, because that is not the point here. For example there is only very little verifications on the input arguments, and the programs could easily be crashed if bad arguments are given.

## Image

#### Description
This example is some kind of an image labyrinth solver. I takes an image where white pixels represent the possible paths, and every other colour represents the walls. The result should be quite fast on images of moderate sizes, but beware of really big or unsolvable ones. For example, the 001.png image is solved in approximately 80ms on my desktop. It is not guaranteed to find the best way because of the nature of A*

#### Building
You will need to have [SFML 2](http://www.sfml-dev.org/index.php) installed on your computer in order to biuld this example ; it is needed to load and save images.

####Usage
Run with 5 arguments :
* the path to the image file
* x coordinate of the start pixel
* y coordinate of the start pixel
* x coordinate of the goal pixel
* y coordinate of the goal pixel

So if I compile the example and name the executable file image.exe, to solve the example image I could write the following command :

``` $ image.exe 001.png 1 1 599 479 ```


## Cities

#### Description
This example is a case of the famous [shortest past problem](http://en.wikipedia.org/wiki/Shortest_path_problem) where we want to find the shortest path from a city to another on a road network. I provided a small text file with the distances between some of the main French cities. It's about USA not being the center of the world, ya know :-p.

####Usage
Run with 3 arguments :
* the path to the text file containing the cities network
* the start city
* the goal city

To compute the shortest path between Besançon and Bordeaux with my France.txt file, run the following command (with the output executable named cities.exe) :

``` $ cities.exe France.txt Besançon Bordeaux ```
