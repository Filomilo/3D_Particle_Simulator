#pragma once
#include "Polygonal.h"
#include <cmath>
# define M_PI           3.14159265358979323846 
class Sphere :
    public Polygonal
{

private:
    Vector3f getNormalVectroOfPoint(int pointIndx)
    {
       std::shared_ptr<Vector3f> posRef = std::dynamic_pointer_cast<Vector3f>( this->points.at(pointIndx)->getAttribute("P"));
       Vector3f pos = *posRef;
       pos.normalize();
       return pos;

    }



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
        
        float columnwidthUv = 1.0f / columns;
        float rowHeightUv = 1.0f / rows;
        for (int c = 0; c < columns; c++) {

           int  secndColum = (c+1) % (columns);
           float columnsStart = columnwidthUv * c;

           this->addVertex(0, getNormalVectroOfPoint(0), { 1.0f - columnsStart+ columnwidthUv/2.0f, 1});
           this->addVertex((rows * c) + 1, getNormalVectroOfPoint((rows * c) + 1), { 1.0f - columnsStart , 1-rowHeightUv });
           this->addVertex(1 + (rows * (secndColum)), getNormalVectroOfPoint(1 + (rows * (secndColum))), { 1.0f - columnsStart + columnwidthUv, 1- rowHeightUv });
           



            this->addFace({ facwItereaote++,facwItereaote++,facwItereaote++ });
            for (int r = 1; r < rows-1; r++) {

                Vector2f uv1 = Vector2f(1.0f - (columnwidthUv * c),1.0f-( r * rowHeightUv));
                Vector2f uv2 = Vector2f(1.0f - (columnwidthUv * c), 1.0f - (r * rowHeightUv + rowHeightUv));
                Vector2f uv3 = Vector2f(1.0f -( columnwidthUv * c + columnwidthUv), 1.0f -( r * rowHeightUv));
                Vector2f uv4 = Vector2f(1.0f -( columnwidthUv * c + columnwidthUv), 1.0f -( r * rowHeightUv + rowHeightUv));


                this->addVertex((rows * c) + r, getNormalVectroOfPoint((rows * c) + r), uv1);
                this->addVertex((rows * c) + r + 1, getNormalVectroOfPoint((rows * c) + r + 1), uv2);
                this->addVertex(r + 1 + (rows * (secndColum)), getNormalVectroOfPoint(r + 1 + (rows * (secndColum))), uv4);
                this->addVertex(r + (rows * (secndColum)), getNormalVectroOfPoint(r + (rows * secndColum)), uv3);


               this->addFace({ facwItereaote++,facwItereaote++,facwItereaote++,facwItereaote++ });
            }
            
            this->addVertex(columns * rows, getNormalVectroOfPoint(columns * rows), { 1.0f - columnsStart + columnwidthUv / 2.0f, 0 });
            this->addVertex((rows * c) + rows - 1, getNormalVectroOfPoint((rows * c) + rows - 1), { 1.0f - columnsStart ,  rowHeightUv });
            this->addVertex(rows - 1 + (rows * (secndColum)), getNormalVectroOfPoint(rows - 1 + (rows * (secndColum))), { 1.0f - columnsStart + columnwidthUv,rowHeightUv });
            
            this->addFace({ facwItereaote++,facwItereaote++,facwItereaote++ });

        }



    }


};

