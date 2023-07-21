#include <SFML/Graphics.hpp>
#include <cuda_runtime.h>
#include <iostream>

const int WWIDTH = 1920;
const int WHEIGHT = 1080;

__global__ void drawCircle(unsigned char* pixels,
                            int width,
                            int height,
                            int centerX,
                            int centerY,
                            int radius,
                            unsigned char r,
                            unsigned char g,
                            unsigned char b)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= width || y >= height)
        return;

    int dx = x - centerX;
    int dy = y - centerY;
    int distanceSquared = dx * dx + dy * dy;

    if (distanceSquared <= radius * radius)
    {
        int index = (y * width + x) * 4;
        pixels[index] = r;
        pixels[index + 1] = g;
        pixels[index + 2] = b;
        pixels[index + 3] = 255;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WWIDTH, WHEIGHT), "Vision Therapy");
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.create(WWIDTH, WHEIGHT);
    sf::Sprite sprite(texture);

    unsigned char* pixels = new unsigned char[WWIDTH * WHEIGHT * 4];
    cudaMallocManaged(&pixels, WWIDTH * WHEIGHT * 4);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks(WWIDTH / threadsPerBlock.x, WHEIGHT / threadsPerBlock.y);

    
    int radius = 50;
    int speed = 10;

    int x = radius;
    int y = (WHEIGHT / 2) - radius;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    window.close();
                    break;
                }
            }
        }

        x += speed;
        if (x + radius > WWIDTH) {
            x = WWIDTH - radius;
            speed = -speed;
        } else if (x - radius < 0) {
            x = radius;
            speed = -speed;
        }

        // Clear the pixel array
        cudaMemset(pixels, 0, WWIDTH * WHEIGHT * 4);

        drawCircle<<<numBlocks, threadsPerBlock>>>(pixels,
                                                    WWIDTH, WHEIGHT,
                                                    x,
                                                    y,
                                                    radius,
                                                    0, 255, 0);
        
        cudaDeviceSynchronize();

        texture.update(pixels, WWIDTH, WHEIGHT, 0, 0);
        window.clear(sf::Color::Yellow);
        window.draw(sprite);
        window.display();
    }

    cudaFree(pixels);

    return 0;
}