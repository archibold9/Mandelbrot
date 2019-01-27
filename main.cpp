//
//  main.cpp
//  Mandlebrot
//
//  Created by Tom Sturgeon on 27/01/2019.
//  Copyright © 2019 Tom Sturgeon. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cmath>

using namespace std;

double mapToReal(int x, int imageWidth, double minR, double maxR)
{
    double range = maxR - minR;
    
    return x * (range / imageWidth) + minR;
}

double mapToImaginary(int y, int imageHeight, double minI, double maxI)
{
    double range = maxI - minI;
    return y * (range / imageHeight) + minI;
}

int findMandelbrot(double cr, double ci, int max_iterations)
{
    int i = 0;
    double zr = 0.0, zi = 0.0;
    
    while(i < max_iterations && zr * zr + zi * zi < 4.0 )
    {
        double temp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        i++;
    }
    
    return i;
}

int main(int argc, const char * argv[]) {
    //get inputs from file
    ifstream fin("input.txt");
    int imageWidth, imageHeight, maxN;
    double minR, maxR, minI, maxI;
    
    if(!fin){
        cout << "Could not open specified input file." << endl;
        char * dir = getcwd(NULL, 0); // Platform-dependent, see reference link below
        printf("Current dir: %s", dir);
    }
    
    fin >> imageWidth >> imageHeight >> maxN;
    fin >> minR >> maxR >> minI >> maxI;
    
    fin.close();
    //open output, write ppm header
    ofstream fout("mandelbrot.ppm");
    fout << "P3" << endl;
    fout << imageWidth << " " << imageHeight << endl;
    fout << "256" << endl;
    
    //for each pixel
    for(int y = 0; y < imageHeight; y++)
    {
        for(int x = 0; x < imageWidth; x++)
        {
            double cr = mapToReal(x, imageWidth, minR, maxR);
            
            double ci = mapToImaginary(y, imageHeight, minI, maxI);
            
            
            int n = findMandelbrot(cr, ci, maxN);
            
            //generate interesting colors
            int r = (((int) sinf(n)) % 256);
            //Purple
            int g = (n % 256);
            int b = (n % 256);
            
            //Output!
            
            fout << r << " " << g << " " << b << " ";
        }
        fout << endl;
    }
    fout.close();
    cout << "Done";
}
