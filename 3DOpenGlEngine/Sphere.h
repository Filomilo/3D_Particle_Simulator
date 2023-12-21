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


        //caps
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

    
       // this->addVertecies({ 1,2, 3 + rows, 2 + rows, });
        //this->addFace({ facwItereaote++,facwItereaote++,facwItereaote++ ,facwItereaote++ });
        /**
       
        for(int i=0;i<columns;i++)
        {
            int firstPoint = 0;
            int secondPoint = (1 + (i * rows)) % this->points.size();
            int thirdPoint = (1 + ((i + 1) * rows))%this->points.size();

            this->addVertecies({ 0 ,secondPoint, thirdPoint });
            this->addFace({ facwItereaote++,facwItereaote++,facwItereaote++});
        }


        /*


        int i = 0;
  
        for (int n = 0; n < rows; n++)
        {
            for (int m = 0; m < columns; m++)
            {

                int firstPoint = n * columns + m;
                int secondPoint = firstPoint + 1;
                int thirdPoint = (n + 1) * columns + m;
                int forthPoint = thirdPoint + 1;


                firstPoint %= this->points.size();
                    secondPoint %= this->points.size();
                    thirdPoint %= this->points.size();
                    forthPoint %= this->points.size();

                this->addVertecies({ firstPoint , secondPoint,thirdPoint,forthPoint});
               


                i++;
            }

        }

     
     */

        /*

        this->addVertex(2, { 0.000000, 1.000000, 0.000000 }, { 0.375000, 0.250000 });
        this->addVertex(3, { 0.000000, 1.000000, 0.000000 }, { 0.625000, 0.250000 });
        this->addVertex(5, { 0.000000, 1.000000, 0.000000 }, { 0.625000, 0.500000 });
        this->addVertex(4, { 0.000000, 1.000000 ,0.000000 }, { 0.375000, 0.500000 });
        this->addFace({ 4,5,6,7 });

        this->addVertex(4, { 0.000000, 0.000000, -1.000000 }, { 0.375000 ,0.500000 });
        this->addVertex(5, { 0.000000 ,0.000000, -1.000000 }, { 0.625000 ,0.500000 });
        this->addVertex(7, { 0.000000 ,0.000000, -1.000000 }, { 0.625000, 0.750000 });
        this->addVertex(6, { 0.000000, 0.000000 ,-1.000000 }, { 0.375000 ,0.750000 });
        this->addFace({ 8,9,10,11 });

        this->addVertex(6, { 0.000000, -1.000000, 0.000000 }, { 0.375000, 0.750000 });
        this->addVertex(7, { 0.000000 ,-1.000000, 0.000000 }, { 0.625000, 0.750000 });
        this->addVertex(1, { 0.000000, -1.000000, 0.000000 }, { 0.625000, 1.000000 });
        this->addVertex(0, { 0.000000, -1.000000 ,0.000000 }, { 0.375000, 1.000000 });
        this->addFace({ 12,13,14,15 });

        this->addVertex(1, { 1.000000, 0.000000, 0.000000 }, { 0.625000, 0.000000 });
        this->addVertex(7, { 1.000000 ,0.000000, 0.000000 }, { 0.87500 ,0.000000 });
        this->addVertex(5, { 1.000000 ,0.000000, 0.000000 }, { 0.875000, 0.250000 });
        this->addVertex(3, { 1.000000 ,0.000000, 0.000000 }, { 0.625000, 0.250000 });
        this->addFace({ 16,17,18,19 });

        this->addVertex(6, { -1.000000, 0.000000, 0.000000 }, { 0.125000, 0.000000 });
        this->addVertex(0, { -1.000000 ,0.000000, 0.000000 }, { 0.375000, 0.000000 });
        this->addVertex(2, { -1.000000 ,0.000000, 0.000000 }, { 0.375000,0.250000 });
        this->addVertex(4, { -1.000000, 0.000000, 0.000000 }, { 0.125000, 0.250000 });
        this->addFace({ 20,21,22,23 });

       */ 

    }


};

