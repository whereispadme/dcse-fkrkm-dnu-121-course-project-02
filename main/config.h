#ifndef CONFIG_H
#define CONFIG_H

class Config
{

protected:
    unsigned int posX;
    unsigned int posY;
    unsigned int width;
    unsigned int length;

public:
    Config();
    Config(Config *);
    Config(unsigned int, unsigned int, unsigned int, unsigned int);
    ~Config();

    unsigned int getPosX();
    unsigned int getPosY();
    unsigned int getWidth();
    unsigned int getLength();

};

#endif
