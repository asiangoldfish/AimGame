/**
 * Shared header containing mathematical functions
 */

#pragma once

#include <random>
#include <iostream>

const float PI = 3.1415f;

/**
 * @brief Linear interpolation between start and end value
 * @param start Start value
 * @param end End value
 * @param t Control value that determines where between the start and end
 *			value the return value should be at
 * @return A value between start and end, depending on t
*/
float lerp(float start, float end, float t)
{
	return start * (1 - t) + end * t;
}

/**
 * @brief Generate a random number between 0.0 and 1.0
 * @return Random number between 0.0 and 1.0
*/
float rng()
{
    // Setup random number generator
    std::random_device rnddev;
    std::mt19937 gen(rnddev());
    std::uniform_real_distribution<float> dist(0.f, 1.f);

    float myRandomNumber = dist(gen);

    return myRandomNumber;
}

/**
 * @brief Generate a random number between named low and high value
 * @param low Lowest number to generate
 * @param high Highest number to generate
 * @return Random number between lowest and highest number
*/
float rng(float low, float high)
{
    return rng() * (high - low) + low;
}
