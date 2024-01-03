/**
 * @file Cube.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coanintg cube class primitive
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "Polygonal.h"
/**
 * @brief cube class primitve
 * 
 * calss genaitng cube 
 * 
 */
class Cube : public Polygonal
{
public:

/**
 * @brief Construct a new Cube object
 * 
 * @param size 
 */
    Cube(float size)
    {

        this->addPoints({
            {-size / 2, -size / 2, size / 2},
             {size / 2, -size / 2, size / 2},
             {-size / 2, size / 2, size / 2},
             {size / 2, size / 2, size / 2},
             {-size / 2, size / 2 ,-size / 2},
            {size / 2, size / 2, -size / 2},
            {-size / 2, -size / 2, -size / 2},
            {size / 2, -size / 2, -size / 2}
            });


       this->addVertex(0, Vector3f( 0.000000, 0.000000 ,1.000000 ), Vector2f( 0.375000, 0.000000 ));
        this->addVertex(1, { 0.000000, 0.000000, 1.000000 }, { 0.625000 ,0.000000  });
        this->addVertex(3, { 0.000000, 0.000000 ,1.000000 }, { 0.625000, 0.250000 });
        this->addVertex(2, { 0.000000, 0.000000, 1.000000 }, { 0.375000, 0.250000 });
        


         this->addFace({ 0,1,2,3 });


         
        this->addVertex(2, { 0.000000, 1.000000, 0.000000 }, { 0.375000, 0.250000 });
        this->addVertex(3, { 0.000000, 1.000000, 0.000000 }, { 0.625000, 0.250000  });
        this->addVertex(5, { 0.000000, 1.000000, 0.000000 }, { 0.625000, 0.500000});
        this->addVertex(4, { 0.000000, 1.000000 ,0.000000 }, { 0.375000, 0.500000 });
        this->addFace({ 4,5,6,7 });

        this->addVertex(4, { 0.000000, 0.000000, -1.000000 }, { 0.375000 ,0.500000 });
        this->addVertex(5, { 0.000000 ,0.000000, -1.000000 }, { 0.625000 ,0.500000 });
        this->addVertex(7, { 0.000000 ,0.000000, -1.000000 }, { 0.625000, 0.750000});
        this->addVertex(6, { 0.000000, 0.000000 ,-1.000000 }, { 0.375000 ,0.750000});
        this->addFace({ 8,9,10,11 });

        this->addVertex(6, { 0.000000, -1.000000, 0.000000 }, { 0.375000, 0.750000 });
        this->addVertex(7, { 0.000000 ,-1.000000, 0.000000 }, { 0.625000, 0.750000 });
        this->addVertex(1, { 0.000000, -1.000000, 0.000000 }, { 0.625000, 1.000000});
        this->addVertex(0, { 0.000000, -1.000000 ,0.000000 }, { 0.375000, 1.000000 });
        this->addFace({ 12,13,14,15 });
       
        this->addVertex(1, { 1.000000, 0.000000, 0.000000 }, { 0.625000, 0.000000});
        this->addVertex(7, { 1.000000 ,0.000000, 0.000000 }, { 0.87500 ,0.000000 });
        this->addVertex(5, { 1.000000 ,0.000000, 0.000000 }, { 0.875000, 0.250000 });
        this->addVertex(3, { 1.000000 ,0.000000, 0.000000 }, { 0.625000, 0.250000  });
        this->addFace({ 16,17,18,19 });

        this->addVertex(6, { -1.000000, 0.000000, 0.000000 }, { 0.125000, 0.000000});
        this->addVertex(0, { -1.000000 ,0.000000, 0.000000 }, { 0.375000, 0.000000 });
        this->addVertex(2, { -1.000000 ,0.000000, 0.000000 }, { 0.375000,0.250000});
        this->addVertex(4, { -1.000000, 0.000000, 0.000000 }, { 0.125000, 0.250000  });
        this->addFace({ 20,21,22,23 });
       
    }



};

