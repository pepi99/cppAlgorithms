#ifndef EXERCISES_H
#define EXERCISES_H

#include <list>
#include <set>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>


////////////////// Exercise 1 ////////////////////////////////////
std::pair<float, float> Statistics(const std::list<float> &values) {
    float mean = 0;
    for (float i: values) {
        mean = mean + i;
    }
    mean = mean / values.size();

    float SD = 0;
    for (float f: values) {
        SD = SD + powf(f - mean, 2.0);

    } // now we have the whole sum
    SD = SD / values.size();
    SD = sqrt(SD);
    return std::make_pair(mean, SD);
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 2 ////////////////////////////////////
class TreeVisitor {

public:
    float visitTree(const Tree &tree, bool countOnlyEven) {
        if (!countOnlyEven) {
            return visitTreeNormal(tree);;
        } else {
            return visitTreeEven(tree, true);;
        }
    }

    float visitTreeNormal(const Tree &tree) {
        float answer = tree.value;
        for (Tree t: tree.children) {
            answer = answer + visitTreeNormal(t);
        }
        return answer;
    }

    float visitTreeEven(const Tree &tree, bool isEven) {
        float answer = 0;
        if (isEven) {
            answer = tree.value;
            for (Tree t: tree.children) {
                answer += visitTreeEven(t, !isEven);
            }
        } else {
            for (Tree t: tree.children) {
                answer += visitTreeEven(t, !isEven);
            }
        }
        return answer;
    }
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 3 ////////////////////////////////////
class Complex {
public:
    Complex(float reall, float imaginary) {
        real = reall;
        im = imaginary;
    };
    float real, im;

    Complex operator+(const Complex &other) {
        return Complex(real + other.real, im + other.im);
    }

    Complex operator-(const Complex &other) {
        return Complex(real - other.real, im - other.im);

    }

    Complex operator*(const Complex &other) {
        return Complex(real * other.real - im * other.im, real * other.im + other.real * im);

    }

};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 4 ////////////////////////////////////
float WaterLevels(std::list<float> heights) {
    std::vector<float> vector;
    for (float c: heights) {
        vector.push_back(c);
    }
    float answer = 0;
    int currStart = 0;
    int currEnd = 0;
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i] < vector[i + 1]) {
            currEnd = i + 1;
            while ((vector[currEnd] < vector[currEnd + 1]) && currEnd < vector.size() &&
                   (vector[currStart] > vector[currEnd])) {
                currEnd = currEnd + 1;
            }
            // fill everything in between with the minimum of the two walls
            float min = std::min(vector[currEnd], vector[currStart]);
            for (int j = currStart + 1; j < currEnd; j++) {
                float toAdd = min - vector[j];
                answer = answer + toAdd;
            }
            currStart = currEnd;
        }
    }
    return answer;
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 5 ////////////////////////////////////
typedef std::pair<int, int> location;

int Labyrinth(std::set<std::pair<location, location>> labyrinth, int size) {
    int x = size - 1;
    location destination(x, x);
    std::queue<std::pair<location, int>> q;
    std::set<location> visited;
    std::pair<location, int> topush = std::make_pair(location(0, 0), 0);
    q.push(topush);

    while (!q.empty()) {
        std::pair<location, int> element = q.front();
        location loc = element.first;
        if (loc == destination) {
            return element.second + 1;
        }

        q.pop();
        visited.insert(loc);
        // define locations
        location up = location(loc.first, loc.second - 1);
        int aUp = up.second;
        bool bUp = visited.count(up) == 0;
        location down = location(loc.first, loc.second + 1);
        int aDown = down.second;
        bool bDown = visited.count(down) == 0;

        location right = location(loc.first + 1, loc.second);
        int aRight = right.first;
        bool bRight = visited.count(right) == 0;

        location left = location(loc.first - 1, loc.second);
        int aLeft = left.first;
        bool bLeft = visited.count(left) == 0;

        // now start adding to the q with new distances + some checks
        if (aDown < size && bDown && labyrinth.count(make_pair(loc, down)) == 0 &&
            labyrinth.count(make_pair(down, loc)) == 0) {
            std::pair<location, int> toAdd = std::make_pair(down, element.second + 1);
            q.push(toAdd);
        }
        if (aUp >= 0 && bUp && labyrinth.count(std::make_pair(loc, up)) == 0 &&
            labyrinth.count(std::make_pair(up, loc)) == 0) {
            std::pair<location, int> toAdd = std::make_pair(up, element.second + 1);
            q.push(toAdd);
        }
        if (aLeft < size && bLeft && labyrinth.count(make_pair(loc, left)) == 0 &&
            labyrinth.count(make_pair(left, loc)) == 0) {
            std::pair<location, int> toAdd = std::make_pair(left, element.second + 1);
            q.push(toAdd);
        }
        if (aRight < size && bRight && labyrinth.count(make_pair(loc, right)) == 0 &&
            labyrinth.count(make_pair(right, loc)) == 0) {
            std::pair<location, int> toAdd = std::make_pair(right, element.second + 1);
            q.push(toAdd);
        }


    }

}


//////////////////////////////////////////////////////////////////

#endif