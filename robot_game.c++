// 2751. Robot Collisions
// Solved
// Hard
// Topics
// Companies
// Hint
// There are n 1-indexed robots, each having a position on a line, health, and movement direction.

// You are given 0-indexed integer arrays positions, healths, and a string directions (directions[i] is either 'L' for left or 'R' for right). All integers in positions are unique.

// All robots start moving on the line simultaneously at the same speed in their given directions. If two robots ever share the same position while moving, they will collide.

// If two robots collide, the robot with lower health is removed from the line, and the health of the other robot decreases by one. The surviving robot continues in the same direction it was going. If both robots have the same health, they are both removed from the line.

// Your task is to determine the health of the robots that survive the collisions, in the same order that the robots were given, i.e. final heath of robot 1 (if survived), final health of robot 2 (if survived), and so on. If there are no survivors, return an empty array.

// Return an array containing the health of the remaining robots (in the order they were given in the input), after no further collisions can occur.

// Note: The positions may be unsorted.

 
 

// Example 1:



// Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
// Output: [2,17,9,15,10]
// Explanation: No collision occurs in this example, since all robots are moving in the same direction. So, the health of the robots in order from the first robot is returned, [2, 17, 9, 15, 10].
// Example 2:



// Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
// Output: [14]
// Explanation: There are 2 collisions in this example. Firstly, robot 1 and robot 2 will collide, and since both have the same health, they will be removed from the line. Next, robot 3 and robot 4 will collide and since robot 4's health is smaller, it gets removed, and robot 3's health becomes 15 - 1 = 14. Only robot 3 remains, so we return [14].

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        vector<tuple<int, int, char, int>> robots(n);
        for (int i = 0; i < n; ++i) {
            robots[i] = {positions[i], healths[i], directions[i], i};
        }
        sort(robots.begin(), robots.end());
        stack<tuple<int, int, char, int>> st;
        vector<int> result(n, -1);

        for (const auto& robot : robots) {
            int pos, health, index;
            char direction;
            tie(pos, health, direction, index) = robot;

            if (direction == 'R') {
                st.push(robot);
            } else {
                while (!st.empty() && health > 0) {
                    auto& topRobot = st.top();
                    int topPos, topHealth, topIndex;
                    char topDirection;
                    tie(topPos, topHealth, topDirection, topIndex) = topRobot;

                    if (topHealth < health) {
                        health -= 1;
                        st.pop();
                    } else if (topHealth > health) {
                        get<1>(st.top()) -= 1;
                        health = 0;
                    } else {
                        st.pop();
                        health = 0;
                    }
                }
                if (health > 0) {
                    result[index] = health;
                }
            }
        }
        while (!st.empty()) {
            auto robot = st.top();
            st.pop();
            int pos, health, index;
            char direction;
            tie(pos, health, direction, index) = robot;
            result[index] = health;
        }
        vector<int> finalResult;
        for (int i = 0; i < n; ++i) {
            if (result[i] != -1) {
                finalResult.push_back(result[i]);
            }
        }

        return finalResult;
    }
};