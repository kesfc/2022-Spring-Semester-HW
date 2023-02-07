#ifndef __polygon_h_
#define __polygon_h_
#include <string>
#include <vector>
#include "utilities.h"

using namespace std;

class Polygon
{
public:
    Polygon(string name, std::vector<Point> vertices) : name_(name), vertices_(vertices)
    {
        if (vertices_.size() < 3)
        {
            throw 1;
        }
    }

    // Destructor
    virtual ~Polygon()
    {
        vertices_.clear();
    }

    // Accessor
    string getName() const
    {
        return name_;
    }

    // Checks
    bool HasAllEqualSides() const
    {
        Vector temp(vertices_[0], vertices_[1]);
        double lenth = temp.Length();
        for (unsigned int i = 0; i < vertices_.size() - 1; ++i)
        {
            temp = Vector(vertices_[i], vertices_[i + 1]);
            if (!EqualSides(temp.Length(), lenth))
            {
                return false;
            }
        }

        return true;
    }

    bool HasAllEqualAngles() const
    {
        double check = Angle(vertices_[vertices_.size() - 1], vertices_[0], vertices_[1]);
        bool equal = true;

        for (unsigned int i = 0; i < vertices_.size() - 2; ++i)
        {
            // For when it need to check last angle
            if (i == vertices_.size() - 3)
            {
                if (!EqualAngles(check, Angle(vertices_[i], vertices_[i + 1], 
                vertices_[i + 2])))
                {
                    equal = false;
                }
                else if (!EqualAngles(check, Angle(vertices_[i + 1], vertices_[i + 2], vertices_[0])))
                {
                    equal = false;
                }
            }
            else
            {
                if (!EqualAngles(check, Angle(vertices_[i], vertices_[i + 1], vertices_[i + 2])))
                {
                    equal = false;
                }
            }
        }

        return equal;
    }

    bool HasARightAngle() const
    {
        bool right = false;

        for (unsigned int i = 0; i < vertices_.size() - 2; ++i)
        {
            // For when it need to check last angle
            if (i == vertices_.size() - 3)
            {
                if (RightAngle(Angle(vertices_[i], vertices_[i + 1], vertices_[i + 2])))
                {
                    right = true;
                }
                else if (RightAngle(Angle(vertices_[i + 1], vertices_[i + 2], vertices_[0])))
                {
                    right = true;
                }
                else if (RightAngle(Angle(vertices_[i + 2], vertices_[0], vertices_[1])))
                {
                    right = true;
                }
            }
            else
            {
                if (RightAngle(Angle(vertices_[i], vertices_[i + 1], vertices_[i + 2])))
                {
                    right = true;
                }
            }
        }

        return right;
    }

protected:
    string name_;
    std::vector<Point> vertices_;
};

class Triangle : public Polygon
{
public:
    Triangle(string name_, std::vector<Point> vertices_) : Polygon(name_, vertices_)
    {
        // Needs 3 sides
        if (vertices_.size() != 3)
        {
            throw 2;
        }
    }
};

class RightTriangle: virtual public Triangle
{
    public:
    RightTriangle(string name_, std::vector<Point> vertices_):  Triangle(name_, vertices_)
    {
        if(!HasARightAngle()){
            throw 89;
        }
    }
};
class IsoscelesTriangle : virtual public Triangle
{
public:
    IsoscelesTriangle(string name_, std::vector<Point> vertices_) : 
    Triangle(name_, vertices_){
        Vector temp(vertices_[0], vertices_[1]);
        Vector temp2(vertices_[0], vertices_[2]);
        Vector temp3(vertices_[1], vertices_[2]);

        // Needs at least two equal sides
        if (!EqualSides(temp.Length(), temp2.Length()))
        {
            if (!EqualSides(temp.Length(), temp3.Length()))
            {
                if (!EqualSides(temp2.Length(), temp3.Length()))
                {
                    throw 3;
                }
            }
        }
    }
};

class IsoscelesRightTriangle: public IsoscelesTriangle, public RightTriangle{
    public:
        IsoscelesRightTriangle(string name_, std::vector<Point> vertices_):
        Triangle(name_, vertices_), IsoscelesTriangle(name_, vertices_), RightTriangle(name_, vertices_){
            Vector temp(vertices_[0], vertices_[1]);
                Vector temp2(vertices_[0], vertices_[2]);
                Vector temp3(vertices_[1], vertices_[2]);
                bool Throw1=true;
                // Needs at least two equal sides
                if (!EqualSides(temp.Length(), temp2.Length()))
                {
                    if (!EqualSides(temp.Length(), temp3.Length()))
                    {
                        if (!EqualSides(temp2.Length(), temp3.Length()))
                        {
                            Throw1=false;
                        }
                    }
                }
            if(!HasARightAngle()||!Throw1){
                throw 77;
            }
        }
};

class EquilateralTriangle : public IsoscelesTriangle
{
public:
    EquilateralTriangle(string name_, std::vector<Point> vertices_) : 
    Triangle(name_, vertices_), IsoscelesTriangle(name_, vertices_)
    {
        // Need all equal sides
        if (!HasAllEqualSides())
        {
            throw 4;
        }
    }
};
class Quadrilateral : public Polygon
{
public:
    Quadrilateral(const std::string &n, const std::vector<Point> &p)
        : Polygon(n, p)
    {
        if (p.size() != 4)
            throw 5;
    }
};
class Rectangle : public Quadrilateral
{
public:
    Rectangle(const std::string &n, const std::vector<Point> &p)
        : Quadrilateral(n, p)
    {
        if(!HasARightAngle()){
            throw 6;
        }
    }
};

class Square : public Rectangle
{
public:
    Square(const std::string &n, const std::vector<Point> &p)
        : Rectangle(n, p)
    {
        if(!HasARightAngle()||!HasAllEqualSides()){
            throw 7;
        }
    }
};

#endif