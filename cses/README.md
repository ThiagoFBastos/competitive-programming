# Tips and tutorials of CSES problems

- [Acyclic Graph Edges](https://github.com/ThiagoFBastos/competitive-programming/blob/main/cses/Acyclic%20Graph%20Edges.cpp)

    Such we always choose the same direction (from the lowest to the highest or the opposite) for all edges, we will never have a cycle because after go from the start vertex we cannot go back to it.

- [Advertisement](https://github.com/ThiagoFBastos/competitive-programming/blob/main/cses/Advertisement.cpp)

    Here if we let fixed the height of the rectangle, then the problem is simple, because we only have to find the leftmost and rightmost positions in the array that this height is the smallest.

- [All Manhattan Distances](https://github.com/ThiagoFBastos/competitive-programming/blob/main/cses/All%20Manhattan%20Distances.cpp)

    The problem is easy if we split the problem in two: find the sum of distances for a scalar coordinate.
    We have to take care with overflow, thus we use a 128 bit integer.

- [And Subset Count](https://github.com/ThiagoFBastos/competitive-programming/blob/main/cses/And%20Subset%20Count.cpp)

    This problem is less straightforward, because to solve it we have to find the count of supermasks that a mask is submask, because the AND (&) of many values is a submask of them. Now, we have a problem that is a mask can have more than 1 submask and because this the count can be incorrect given that a mask has a intersection with it's supermask. To solve this we use the inclusion-exclusion principle.
    We count the number of supermasks given a mask using SOS DP and the inclusion-exclusion is very easy to find: it's only multiply by -1 the masks with a odd number of ones.

- [Another Game](https://github.com/ThiagoFBastos/competitive-programming/blob/main/cses/Another%20Game.cpp)

    If there is a heap with an odd number of coins, the first player can select all heaps with an odd number of coins and 
    remove one coin from them, thus after this all heaps have an even number of coins and in the first player turn he can
    leave all heaps with an even number of coins, making an invariant. Otherwise, if all heaps have an even number of coins
    the strategy is the same, but for the second player.

- [Apartments](https://github.com/ThiagoFBastos/competitive-programming/blob/main/cses/Apartments.cpp)

    The strategy is always choose the apartment with size closer to x - k and that not is greater than x + k, but looking for the desired sizes ordered.

- [Apple Division](https://github.com/ThiagoFBastos/competitive-programming/blob/main/cses/Apple%20Division.cpp)

    Simple bitmask DP split.