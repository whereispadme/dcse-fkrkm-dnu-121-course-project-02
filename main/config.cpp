#include "config.h"

Config::Config()
{

    this->posX = 0;
    this->posY = 0;
    this->width = 0;
    this->length = 0;

}

Config::Config(Config *config)
{

    this->posX = config->posX;
    this->posY = config->posY;
    this->width = config->width;
    this->length = config->length;

}

Config::Config(unsigned int posX, unsigned int posY, unsigned int width, unsigned int length)
{

    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->length = length;

}

Config::~Config()
{
}

unsigned int Config::getPosX()
{

    return this->posX;

}

unsigned int Config::getPosY()
{

    return this->posY;

}

unsigned int Config::getWidth()
{

    return this->width;

}

unsigned int Config::getLength()
{

    return this->length;

}
