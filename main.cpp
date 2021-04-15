/*
 * Lab 01 Comp 139e - Surveying 
 * 
 * Main.cpp - This program calculates the number of streetlights required along
 * an Arc and their positions. Input radius, distance between the ends of the
 * arc and the max spacing allowed between the lights and the program will 
 * return the number of lights needed and the distance from Peg 1 and the angle 
 * off the cord of each light. 
 * 
 * Author: Adam Claxton 
 * Date: Sept 24th 2020
 * 
 * The functions getUserInput and outputResults are from the course website for 
 * comp 139e 
 */
 

#include <cstdlib>
#include <iostream>
#include <cmath>


#define M_PI 3.14 // had to define PI because the compiler didn't include it in cmath 


using namespace std;

void getUserInput (double &radius, double &pegDist, double &spacing);
void outputResults (const double angles[], const double distances[], const int numLights);

/*
 * Prints the result to standard output - command-line interface
 *
 * @param angles Array of angles, referenced to the baseline chord (radians)
 * @param distances Array of distances to the streetlights
 * @param numLights Number of streetlights
 *
 */
void outputResults (const double angles[], const double distances[], const int numLights) {
    cout << numLights << " streetlights are required." << endl;
    
    for (int i=0; i < numLights; i++) {
        cout << "Light " << (i+1) << ": Distance=" << distances[i];
        if (distances[i] > 1.0e-6) {
	    double angle = abs(angles[i] < 1.0e-6) ? 0.0 : angles[i];
            cout << " Angle=" << angle * 180.0/M_PI << " degrees";
        }
        cout << endl;
    }
}

/**
 * Gets input values from the user via a command-line prompt:
 * radius of curvature, distance between pegs, and maximum streetlight spacing
 *
 * @param radius Reference to the radius of curvature
 * @param pegDist Reference to the distance between arc endpoints
 * @param spacing Reference to maximum streetlight spacing
 * 
 */
void getUserInput (double &radius, double &pegDist, double &spacing) {
    cout << "Enter the radius of curvature: ";
    cin >> radius;
    cout << "Enter the distance between the survey pegs at the endpoints: ";
    cin >> pegDist;
    if (pegDist > 2.0 * radius) {
        cerr << "The distance between pegs cannot be more than twice the radius!";
        exit (EXIT_FAILURE);
    }
    cout << "Enter the maximum streetlight spacing along the arc: ";
    cin >> spacing;
}


int main() {
    
    double radius, pegDist,spacing; 
    int numOfLights; 
    
    // get the input parameters from the user  
    getUserInput(radius, pegDist, spacing);

    //Calculates the angles for the triangle of peg1-peg2 and radial center 
    double gammaArcAngle = 2*asin((pegDist/2.00)/radius); // angle at radial center 
    double lamdaArcAngle = (M_PI-gammaArcAngle)/2.00; // angle between cord and radius at peg 1 and 2
    
    // get the Arc Length using the formula (radius * theta) 
    double arcLength = radius*gammaArcAngle; 
    // find how many lights are needed
    numOfLights = ceil(arcLength/spacing)+1; // rounds up using ceil and adds 1 to account for first light
    
    // dynamic arrays to hold the distance and angle of each light 
    double distances[numOfLights]; 
    double angles[numOfLights]; 
    
    //finds the radial angle between each streetlight from the radius 
    double betaAngle = (gammaArcAngle/(numOfLights-1)); 
    
    // calculates the angle and distance from peg1 and the angle off the cord
    for(int i = 0; i < numOfLights; i++){ 
        distances[i] = 2*radius*sin((betaAngle*i)/2); 
        angles[i] = ((M_PI - (betaAngle*i))/2) - lamdaArcAngle;     
    }
    
    // prints all the outputs
    outputResults(angles, distances, numOfLights);
  
    return 0;
}

