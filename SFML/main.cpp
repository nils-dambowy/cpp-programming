#include <SFML/Graphics.hpp>
#include <iostream>

struct Frame{
    sf::IntRect rect;
    double duration;
};

class gameLevel {
    public:
        sf::Sprite g_sprite, e_sprite1, e_sprite2, e_sprite3, sbg1, sbg2;
        sf::Texture texture_grass, texture_earth, bg1, bg2;

        void load_textures() {
            if (!texture_grass.loadFromFile("Grass.png", sf::IntRect(32, 10, 15, 15)))
            {
                std::cout << "error loading texture!";
            }
            texture_grass.setSmooth(true);

            if (!texture_earth.loadFromFile("Grass.png", sf::IntRect(32, 28, 15, 15)))
            {
                std::cout << "error loading texture!";
            }
            texture_earth.setSmooth(true);

            if (!bg1.loadFromFile("Background_1.png"))
            {
                std::cout << "error loading texture!";
            }
            bg1.setSmooth(true);

            if (!bg2.loadFromFile("Background_2.png"))
            {
                std::cout << "error loading texture!";
            }
            bg2.setSmooth(true);
        }

        void set_textures() {
            //ground sprites
            g_sprite.setTexture(texture_grass);
            e_sprite1.setTexture(texture_earth);
            e_sprite2.setTexture(texture_earth);
            e_sprite3.setTexture(texture_earth);

            // applying background textures
            sbg1.setTexture(bg1);
            sbg2.setTexture(bg2);
            sbg1.setScale(1.6f, 2.2f); // scaling, so it fits the portion of the screen
            sbg2.setScale(1.6f, 2.2f);
        }

        void create_ground(sf::RenderWindow& window){
            // takes reference as input, since sf::RenderWindow  is non copyable
            // create ground 

            window.draw(sbg1);
            window.draw(sbg2);
            for (int i = 0; i < 53; i++) {
                float x_pos = 15.0f * i;
                g_sprite.setPosition(sf::Vector2f(x_pos, 540.0f));
                e_sprite1.setPosition(sf::Vector2f(x_pos, 555.0f));
                e_sprite2.setPosition(sf::Vector2f(x_pos, 570.0f));
                e_sprite3.setPosition(sf::Vector2f(x_pos, 585.0f));

                window.draw(g_sprite);
                window.draw(e_sprite1);
                window.draw(e_sprite2);
                window.draw(e_sprite3);
            }
        }
};

class Player {

    public:
        // intial location on the screen
        int x;
        int y;
        int direction = 0; // 0 = facing right, 1 = facing left
        sf::Sprite player_sprite;
        sf::Texture run1, run2, run3, run4, run5, run6, run7, run8, run9, run10, idle;
        // run_animation_array run = { run1, run2, run3, run4, run5, run6, run7, run8, run9, run10 };

        void load_texture() {
            if (!run1.loadFromFile("running.png", sf::IntRect(41, 41, 35, 37)))
            {
                std::cout << "error loading texture!";
            }
            run1.setSmooth(true);

            if (!run2.loadFromFile("running.png", sf::IntRect(164, 42, 30, 37)))
            {
                std::cout << "error loading texture!";
            }
            run2.setSmooth(true);

            if (!run3.loadFromFile("running.png", sf::IntRect(288, 42, 30, 37)))
            {
                std::cout << "error loading texture!";
            }
            run3.setSmooth(true);

            if (!run4.loadFromFile("running.png", sf::IntRect(405, 42, 30, 37)))
            {
                std::cout << "error loading texture!";
            }
            run4.setSmooth(true);

            if (!run5.loadFromFile("running.png", sf::IntRect(524, 40, 30, 37)))
            {
                std::cout << "error loading texture!";
            }
            run5.setSmooth(true);

            if (!run6.loadFromFile("running.png", sf::IntRect(641, 41, 30, 37)))
            {
                std::cout << "error loading texture!";
            }
            run6.setSmooth(true);

            if (!run7.loadFromFile("running.png", sf::IntRect(764, 43, 30, 37)))
            {
                std::cout << "error loading texture!";
            }
            run7.setSmooth(true);

            if (!run8.loadFromFile("running.png", sf::IntRect(886, 43, 30, 37)))
            {
                std::cout << "error loading texture!";
            }
            run8.setSmooth(true);

            if (!run9.loadFromFile("running.png", sf::IntRect(1006, 42, 30, 37)))
            {
                std::cout << "error loading texture!";
            }
            run9.setSmooth(true);

            if (!run10.loadFromFile("running.png", sf::IntRect(1123, 41, 30, 37)))
            {
                std::cout << "error loading texture!";
            }
            run10.setSmooth(true);

            if (!idle.loadFromFile("idle.png", sf::IntRect(404, 42, 20, 37)))
            {
                std::cout << "error loading texture!";
            }
            run10.setSmooth(true);
        }

        void move_right(){
            if (20 <= Player::x && Player::x <= 765) {
                direction = 0;
                change_direction(direction);
                Player::player_sprite.setPosition(Player::x += 10, Player::y);
            }
        }

        void move_left() {
            if (30 <= Player::x && Player::x <= 775) {
                direction = 1;
                change_direction(direction);
                Player::player_sprite.setPosition(Player::x -= 10, Player::y);
            }
        }

        void move_down() {
            if (0 <= Player::y && Player::y < 494) {
                Player::player_sprite.setPosition(Player::x, Player::y += 10);
            }
        }

        void move_up() {
            if (10 <= Player::y && Player::y < 504) {
                Player::player_sprite.setPosition(Player::x, Player::y -= 10);
            }
        }

        void change_direction(int dir) {
            if (dir != 0) {
                // check if character is moving to the left, flip sprite
                player_sprite.setScale(-1.f, 1.f);
            }
            else if(dir == 0){
                //set back to normal, if dir = 0
                player_sprite.setScale(1.f, 1.f);
            }
        }
};

class Animation {
    std::vector<Frame> frames;
    double totalLength;
    double totalProgress;
    sf::Sprite *target;

    public:
        Animation(sf::Sprite& target) {
            this->target = &target;
            totalProgress = 0.0;
        }

        void addFrame(Frame&& frame) {
            frames.push_back(std::move(frame));
            totalLength += frame.duration;
        }

        void update(double elapsed) {
            totalProgress += elapsed;
            double progress = totalProgress;

            for (auto frame : frames) {
                progress -= (*frame).duration;

                if (progress <= 0.0 || &(frame) == &frames.back()) {
                    target->setTextureRect((*frame).rect());
                    break;
                }
            }
        }
};


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(795, 600), "My window");

    // create game_level
    gameLevel gl;
    gl.load_textures();
    gl.set_textures();
   
    // create player object
    Player player_obj;
    player_obj.x = 30;
    player_obj.y = 503;
    player_obj.load_texture();
    player_obj.player_sprite.setTexture(player_obj.idle);

    // Create Animation
    Animation animation(player_obj.player_sprite);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // clear the window with black color
        // window.clear(sf::Color::Blue);
        gl.create_ground(window);

        //character sprite
        player_obj.player_sprite.setTexture(player_obj.idle);

        // intial character setup
        player_obj.player_sprite.setPosition(player_obj.x, player_obj.y);

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::W) {
                    player_obj.move_up();
                }

                if (event.key.code == sf::Keyboard::D) {
                    player_obj.move_right();
                }

                if (event.key.code == sf::Keyboard::A) {
                    player_obj.move_left();
                }

                if (event.key.code == sf::Keyboard::S) {
                    player_obj.move_down();
                }
            }
        }
        window.draw(player_obj.player_sprite);
        window.display();
    }
    return 0;
}