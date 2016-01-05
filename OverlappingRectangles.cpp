//
//  main.cpp
//  InterviewPrep
//
//  Created by Clifton Gordon on 11/24/15.
//  Copyright © 2015 Clifton Gordon. All rights reserved.
//

#include <iostream>
#include <sstream>

using namespace std;

class Rectangle
{
private:
    int m_x, m_y;
    int m_width, m_height;
    
public:
    Rectangle(int x, int y, int width, int height)
        : m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
    {}
    
    Rectangle()
        : m_x(0)
        , m_y(0)
        , m_width(0)
        , m_height(0)
    {}
    
    int GetX() { return m_x; }
    int GetY() { return m_y; }
    int GetWidth() { return m_width; }
    int GetHeight() { return m_height; }
    
    string ToString()
    {
        ostringstream resultString;
        resultString << "(" << m_x << ", " << m_y << ", " << m_width << ", " << m_height << ")";
        
        return resultString.str();
    }
};

Rectangle FindIntersection(Rectangle &r1, Rectangle &r2)
{
    int x, y, width, height;
    
    x = max(r1.GetX(), r2.GetX());
    y = max(r1.GetY(), r2.GetY());
    
    width = min(r1.GetX() + r1.GetWidth(), r2.GetX() + r2.GetWidth()) - x;
    height = min(r1.GetY() + r1.GetHeight(), r2.GetY() + r2.GetHeight()) - y;
    
    if (width <= 0 || height <= 0)
        throw exception();
    
    return Rectangle(x, y, width, height);
}


int main(int argc, const char * argv[]) {
    
    Rectangle r1(4, 1, 1, 2);
    Rectangle r2(1, 2, 5, 2);
    
    cout << FindIntersection(r1, r2).ToString() << endl;
    
    Rectangle r3(0, 0, 2, 3);
    Rectangle r4(1, 1, 3, 3);
    
    cout << FindIntersection(r3, r4).ToString() << endl;
    
    Rectangle r5(4, 5, 2, 10);
    Rectangle r6(4, 5, 2, 10);
    cout << FindIntersection(r5, r6).ToString() << endl;
    
    try
    {
        Rectangle r7(0, 0, 2, 4);
        Rectangle r8(5, 8, 3, 2);
        cout << FindIntersection(r7, r8).ToString() << endl;
    }
    catch (exception)
    {
        cout << "Caught an exception -- no overlap!" << endl;
    }
    
    try
    {
        Rectangle r9(2, 2, 3, 8);
        Rectangle r10(5, 2, 8, 4);
        cout << FindIntersection(r9, r10).ToString() << endl;
    }
    catch (exception)
    {
        cout << "Caught an exception -- no overlap!" << endl;
    }
    
    return 0;
}
