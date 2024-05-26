#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <array>
#include <time.h>

using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class Platform {
private:
    int _hight;
    int _width;
    float _startX;
    float _startY;
    sf::RectangleShape shape;
    float _velocity;
public:
    const float PLATFORM_VELOCITY = 1;
    Platform() {
        _velocity = 0;
        _hight = 20; _width = 100;
        _startX = WINDOW_WIDTH / 2 - _width / 2;
        _startY = WINDOW_HEIGHT - _hight - 10;
        shape.setSize(sf::Vector2f(100, 20));
        shape.setFillColor(sf::Color(128, 0, 128));
        shape.setPosition(_startX, _startY);
    }

    void moving() {
        shape.move(_velocity, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && shape.getPosition().x > 0) {
            _velocity = -0.2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && shape.getPosition().x + shape.getSize().x < WINDOW_WIDTH) {
            _velocity = 0.2;
        }
        else {
            _velocity = 0.0;
        }
    }

    void restart() {
        _velocity = 0;
        shape.setPosition(_startX, _startY);
    }

    sf::RectangleShape& getShape() {
        return shape;
    }

};

class Block {
private:
    bool destroy;
    sf::RectangleShape shape;
    int destroy_blocks;
public:
    Block(float startX, float startY) {
        destroy = false;
        destroy_blocks = 0;
        shape.setSize(sf::Vector2f(65, 30));
        shape.setFillColor(Color(0 + rand() % 255, 0 + rand() % 255, 0 + rand() % 255));
        shape.setPosition(startX, startY);
    }

    bool get_destroy() {
        return destroy;
    }

    void set_destroy(bool flag = true) {
        destroy = flag;
        if (flag) destroy_blocks++;
    }

    RectangleShape& getShape() {
        return shape;
    }

};

class Ball {
private:
    float _radius;
    float _startX;
    float _startY;
    float _velocityX, _velocityY;
    sf::CircleShape shape;
    sf::Vector2f velocity;

    void collision_wall(bool& GameOver) {
        if (shape.getPosition().x <= 0 || shape.getPosition().x + 2 * shape.getRadius() >= WINDOW_WIDTH) {
            velocity.x = -velocity.x;
        }
        if (shape.getPosition().y <= 0) {
            velocity.y = -velocity.y;
        }
        if (shape.getPosition().y + 2 * shape.getRadius() >= WINDOW_HEIGHT) {
            GameOver = true;
        }
    }

    void collision_platform(Platform& plat) {
        FloatRect ballBounds = shape.getGlobalBounds();
        FloatRect platformBounds = plat.getShape().getGlobalBounds();

        if (ballBounds.intersects(platformBounds)) {
            if (ballBounds.top + ballBounds.height > platformBounds.top && ballBounds.top + ballBounds.height < platformBounds.top + plat.getShape().getSize().y && velocity.y > 0) {
                velocity.y = -velocity.y;
            }
            else if (ballBounds.top < platformBounds.top + platformBounds.height && ballBounds.top > platformBounds.top && velocity.y < 0) {
                velocity.y = -velocity.y;
            }
            else if (ballBounds.left + ballBounds.width > platformBounds.left &&
                ballBounds.left + ballBounds.width < platformBounds.left + plat.getShape().getSize().x && velocity.x > 0) {
                velocity.x = -velocity.x;
            }
            else if (ballBounds.left < platformBounds.left + platformBounds.width &&
                ballBounds.left > platformBounds.left && velocity.x < 0) {
                velocity.x = -velocity.x;
            }
        }
    }

    void collision_block(std::vector<Block>& blocks) {
        for (auto& block : blocks) {
            if (block.get_destroy() != true && shape.getGlobalBounds().intersects(block.getShape().getGlobalBounds())) {
                block.set_destroy();
                velocity.y = -velocity.y;
            }
        }
    }

public:
    Ball() {
        _radius = 10;
        _startX = WINDOW_WIDTH / 2 - _radius; _startY = WINDOW_HEIGHT / 2 - _radius;
        _velocityX = 0.05; _velocityY = -0.05;
        shape.setRadius(_radius);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(_startX, _startY);
        velocity.x = _velocityX;
        velocity.y = _velocityY;
    }
    void moving(Platform& plat, std::vector<Block>& blocks, bool& GameOver) {
        shape.move(velocity);
        collision_wall(GameOver);
        collision_platform(plat);
        collision_block(blocks);
    }
    sf::CircleShape& getShape() {
        return shape;
    }
};

std::vector<Block> gener_blocks() {
    std::vector<Block> blocks;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            blocks.emplace_back(79 * i + 10, 40 * j + 10);
        }
    }
    return blocks;
}

int give_destroy_blocks(std::vector<Block>& blocks) {
    int total = 0;
    for (auto& block : blocks) {
        if (block.get_destroy() == true) {
            total += 1;
        }
    }
    return total;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arcanoid!");

    Platform platforma = Platform();
    Ball ball = Ball();
    std::vector<Block> blocks = gener_blocks();

    Clock clock;
    float deltaTime = 0.01f; // Уменьшим время между обновлениями экрана

    Font font;
    if (!font.loadFromFile("C:/lessons/sfdsf/Roboto-Italic.ttf")) {
        return -1; // Не удалось загрузить шрифт
    }

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::White);
    gameOverText.setPosition(300, 250);

    Text destroyBlocks;
    destroyBlocks.setFont(font);
    destroyBlocks.setCharacterSize(50);
    destroyBlocks.setFillColor(Color::White);
    destroyBlocks.setPosition(200, 300);

    Text gameR;
    gameR.setFont(font);
    gameR.setCharacterSize(50);
    gameR.setFillColor(Color::White);
    gameR.setPosition(210, 360);

    Text startText;
    startText.setFont(font);
    startText.setCharacterSize(50);
    startText.setFillColor(Color::White);
    startText.setPosition(170, 250);
    startText.setString("Press Enter to Start");

    bool GameOver = false, GameWin = false;
    bool GameStarted = false;

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/lessons/sfdsf/photo.png")) {
        return -1;
    }
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::R) {
                    GameOver = false;
                    GameStarted = true;
                    ball = Ball();
                    blocks = gener_blocks(); 
                    platforma.restart();
                    for (auto& block : blocks) {
                        block.set_destroy(false); 
                    }
                }
                else if (event.key.code == Keyboard::Enter && !GameStarted) {
                    GameStarted = true;
                }
            }
        }
        if (GameStarted && !GameOver) {
            platforma.moving();
            ball.moving(platforma, blocks, GameOver);

            GameWin = true;
            for (auto& block : blocks) {
                if (block.get_destroy() == false) {
                    GameWin = false;
                    break;
                }
            }
            if (GameWin) {
                gameOverText.setString("You Win!");
                gameR.setString("Press 'R' to restart!");
                destroyBlocks.setString("Destroyed Blocks: " + std::to_string(50));
                GameOver = true;
            }
        }
        else {
            if (GameWin == false && GameStarted) {
                gameOverText.setString("You Lose!");
                gameR.setString("Press 'R' to restart!");
                destroyBlocks.setString("Destroyed Blocks: " + std::to_string(give_destroy_blocks(blocks)));
            }
        }

        window.clear();
        window.draw(backgroundSprite); // Отрисовка заднего фона
        if (GameStarted){
            window.draw(platforma.getShape());
            window.draw(ball.getShape());
            for (auto& block : blocks) {
                if (block.get_destroy() == false){
                    window.draw(block.getShape());
                }
            }

            if (GameOver) {
                window.draw(gameOverText);
                window.draw(gameR);
                window.draw(destroyBlocks);
            }
        }
        else {
            window.draw(startText);
        }
        window.display();
    }
    return 0;
}
