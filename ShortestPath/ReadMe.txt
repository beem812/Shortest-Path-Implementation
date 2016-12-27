This is my attempt at implementing Djikstra's shortest path algorithm using a 50k pixel grey scale image as my graph, with the greyscale value of each pixel representing an elevation and the difference in elevation between each pixel representing the cost of movement between those pixels along with a value of 1 for the base movement between pixels regardless of elevation difference.

map1.raw is the original image that is read in as 1 byte integer values.

map2.raw is a greyscale image where the value at each pixel is the weighted distance from the top left pixel (0,0) to every other pixel.

path.raw is the greyscale image with each pixel blacked out with the exception of the pixels representing the path from the top left pixel (0,0) to the bottom right pixel (199,249).


I used a Min heap to store the frontier nodes that still need to be processed. In this implementation each pass results in a rebuilding of the heap due to the order of the heap changing outside of the normal heap calls which would result in an error without the rebuild. Not sure how to avoid that just yet, the complexity for the c++ build heap command is O(N) and no matter what the container of frontier nodes will need to be re-sorted any time a node is updated so this may be the best I can do without a big change in implementation.

