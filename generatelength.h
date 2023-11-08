#ifndef GENERATELENGTH_H
#define GENERATELENGTH_H

#include"tes2.h"

class GenerateLength : public Tes2
{
public:
    GenerateLength();
    ~GenerateLength();
protected:
    void creatl(Point&);
    bool hasrun;
private:
    QVector<int> *lenlist;
    bool check_;
    double r_, angle, arc, rx, ry, rx_, ry_;
    int px, py, r_2, sum, size, length;
    QPointF qpoint1;
};

#endif // GENERATELENGTH_H
