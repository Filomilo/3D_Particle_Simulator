#pragma once
#include "Polygonal.h"
#include <cmath>
# define M_PI           3.14159265358979323846 
class Sphere :
    public Polygonal
{
public:
    Sphere(float size, int columns, int rows)
    {

        for(int n=0;n<rows;n++)
        {
            for (int m = 0; m < columns;m++)
            {
                float x = (sin(M_PI * m / columns) * cos(2*M_PI * n / rows));
                float z = sin(M_PI * m / columns) * sin(2*M_PI * n / rows);
                float y = cos(M_PI * m /columns);
                this->addPoint(x* size, y* size, z* size);

        

            }
     
    
        }
        std::shared_ptr<Vector3f> midP =std::dynamic_pointer_cast<Vector3f>( this->points[0]->getAttribute("P"));
        this->addPoint(midP->x, -midP->y, midP->z);

        int ptIt = 0;


        int facwItereaote = 0;

        int tmp = rows;
        rows = columns;
        columns = tmp;

        for (int c = 0; c < columns; c++) {

           int  secndColum = (c+1) % (columns);
            
            this->addVertecies({ 0 , (rows * c) +1, 1 + (rows*(secndColum)) });
            this->addFace({ facwItereaote++,facwItereaote++,facwItereaote++ });
            for (int r = 1; r < rows-1; r++) {

                this->addVertecies({ (rows * c) + r,(rows * c) + r+1, r+1 + (rows * (secndColum)), r + (rows * (secndColum)) });
               this->addFace({ facwItereaote++,facwItereaote++,facwItereaote++,facwItereaote++ });
            }
            
           this->addVertecies({ columns*rows , (rows * c) + rows-1, rows-1 + (rows * (secndColum)) });
            this->addFace({ facwItereaote++,facwItereaote++,facwItereaote++ });

        }



    }


};

