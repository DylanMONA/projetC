/*#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;

Font font;
Text play;
Text titre;
void chargertexture();

void changertexte(Text& play, string str);



int main() {

    // Parametres graphiques, à replacer au bon endroit
    int MARGIN_LEFT = 100, MARGIN_RIGHT = 100, MARGIN_TOP = 100, MARGIN_BOTTOM = 100;
    int TILE_SIZE = 64;
    int NB_COL = 8, NB_LIGNE = 10;
    unsigned int nbPix_x = MARGIN_LEFT + MARGIN_RIGHT + NB_COL * TILE_SIZE;
    unsigned int nbPix_y = MARGIN_TOP + MARGIN_BOTTOM + NB_LIGNE * TILE_SIZE;
    // définition d'un panneau "central"
    RectangleShape centralPane(Vector2f(NB_COL * TILE_SIZE, NB_LIGNE * TILE_SIZE));
    centralPane.setPosition(MARGIN_LEFT, MARGIN_TOP);
    centralPane.setFillColor(Color::Cyan);

    //definition du niveau
    RectangleShape niv1(Vector2f(NB_COL * TILE_SIZE, 1 * TILE_SIZE));
    niv1.setPosition(MARGIN_LEFT, MARGIN_TOP + 64 * 4);
    RectangleShape casewin(Vector2f(TILE_SIZE, TILE_SIZE));
    casewin.setPosition(MARGIN_LEFT + 64 * 6, MARGIN_TOP + 64 * 4);
    casewin.setFillColor(Color::Red);
    niv1.setFillColor(Color::Green);
    
    // plus une trame (lignes horizontales+verticales). En SFML on peut passer par VertexArray
        // Lines est une sf::enum, VertexArray encapsule autant de points que nécessaires pour ces lignes
    VertexArray trame(Lines, (NB_COL + 1 + NB_LIGNE + 1) * 2);
    // pour les lignes horizontales
    int n = 0;
    for (int i = 0; i <= NB_LIGNE; ++i) {
        trame[n++].position = Vector2f(MARGIN_LEFT, MARGIN_TOP + i * TILE_SIZE);
        trame[n].color = Color::Blue;
        trame[n++].position = Vector2f(nbPix_x - MARGIN_RIGHT, MARGIN_TOP + i * TILE_SIZE);
    }
    // pour les verticales
    for (int i = 0; i <= NB_COL; ++i) {
        trame[n++].position = Vector2f(MARGIN_LEFT + i * TILE_SIZE, MARGIN_TOP);
        trame[n].color = Color::Blue;
        trame[n++].position = Vector2f(MARGIN_LEFT + i * TILE_SIZE, nbPix_y - MARGIN_BOTTOM);
    }
    // on peut (ou pas) distinguer la scène générale cadre+frame et la scène particulière (les cases actuelles)
    vector<Drawable*> scene_generale;
    vector<Drawable*> scene_particuliere;
    
    scene_generale.push_back(&centralPane);
    scene_generale.push_back(&niv1);
    scene_generale.push_back(&casewin);
    scene_generale.push_back(&trame);

    // on place ici la définition d'une texture rouge, probablement qu'il y a mieux à faire (flightweight ? map ?)
    Texture texture_rouge;
    if (!texture_rouge.loadFromFile("texture.jpg")) {
        cerr << "Erreur lors du chargement de l'image" << endl;
        return EXIT_FAILURE;
    }

    //font ecran accueil

    chargertexture();
    play.setFont(font);
    changertexte(play, "play");
    //fond d'ecran
    Texture texture;
    if (!texture.loadFromFile("abc.jpg")) {
        cerr << "Erreur lors du chargement de l'image" << endl;
        return EXIT_FAILURE;
    }
    Sprite fondecran;
    fondecran.setTexture(texture);
    // bouton play

    RectangleShape bouton(Vector2f(400.f, 50.f));
    bouton.setPosition(Vector2f(200.f, 450.f));
    bouton.setFillColor(Color::Blue);
    play.setPosition(Vector2f(375.f, 450.f));
    //titre jeu
    titre.setFont(font);
    changertexte(titre, "Piece out");
    titre.setFillColor(Color::Cyan);
    titre.setPosition(Vector2f(180.f, 100.f));
    titre.setCharacterSize(100);
    RenderWindow accueil(VideoMode(800, 600, 32), "Piece OUT");


    while (accueil.isOpen()) {
        Event eventa;
        Vector2i mousePos = Mouse::getPosition(accueil);
        Vector2f mouseWorldPos = accueil.mapPixelToCoords(mousePos);
        
        while (accueil.pollEvent(eventa)) {
            if (eventa.type == Event::Closed) {
                accueil.close();
                return EXIT_SUCCESS;
            }


            if (eventa.type == Event::MouseButtonPressed) {
                cout << "ok"<<endl;
                if (eventa.mouseButton.button == Mouse::Left) {
                    cout << "ok1" << endl;
                    if (bouton.getGlobalBounds().contains(mouseWorldPos)) {
                        accueil.close();
                    }
                }
            }
        }
        accueil.clear(Color::Yellow);
        //ici on dessine
        accueil.draw(fondecran);
        accueil.draw(titre);
        accueil.draw(bouton);
        accueil.draw(play);
        //mettre a jour la fentre
        accueil.display();
    }

    RenderWindow window{ VideoMode{nbPix_x,nbPix_y},"Piece Out" };
    int win{ 0 };
    int niv{ 1 };
    
    if (niv == 1) {
        Sprite* piece = new Sprite;
        
        piece->setTexture(texture_rouge);
        Vector2u textureSize = texture_rouge.getSize();
        piece->setScale(static_cast<float>(TILE_SIZE) / textureSize.x,
            static_cast<float>(TILE_SIZE) / textureSize.y);
        piece->setPosition(Vector2f(MARGIN_LEFT, MARGIN_TOP + 64 * 4));
        scene_particuliere.push_back(piece);
    }
    while (window.isOpen()) {
        
        int trig_x = -1, trig_y = -1;
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);
        string message = "Mouse Position: (" + to_string(int(mouseWorldPos.x)) + ", " +
            to_string(int(mouseWorldPos.y)) + ")";
        if (centralPane.getGlobalBounds().contains(mouseWorldPos)) {
            Vector2f topLeft = centralPane.getPosition();
            trig_x = (mouseWorldPos.x - topLeft.x) / TILE_SIZE;
            trig_y = (mouseWorldPos.y - topLeft.y) / TILE_SIZE;
            message += " case :" + to_string(trig_x) + " ; " + to_string(trig_y);
        }
        window.setTitle(message);

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed ||
                (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                )
                window.close();
            if (event.type == Event::MouseButtonPressed
                && event.mouseButton.button == Mouse::Left
                && centralPane.getGlobalBounds().contains(mouseWorldPos)) {
                cout << "trigger " << trig_x << " " << trig_y << endl;
                // création d'un sprite pour afficher une case d'exemple
                Sprite* sprite = new Sprite;
                sprite->setTexture(texture_rouge);
                Vector2u textureSize = texture_rouge.getSize();
                sprite->setScale(static_cast<float>(TILE_SIZE) / textureSize.x,
                    static_cast<float>(TILE_SIZE) / textureSize.y);
                sprite->setPosition(centralPane.getPosition() + Vector2f(trig_x * TILE_SIZE, trig_y * TILE_SIZE));
                scene_particuliere.push_back(sprite);
            }

            if (event.type == Event::KeyPressed) {

                if (event.key.code == Keyboard::A) {
                    Sprite* a = new Sprite;
                    a->setTexture(texture_rouge);
                    Vector2u textureSize = texture_rouge.getSize();
                    a->setScale(static_cast<float>(TILE_SIZE) / textureSize.x,
                        static_cast<float>(TILE_SIZE) / textureSize.y);
                    a->setPosition(centralPane.getPosition() + Vector2f(trig_x * TILE_SIZE, trig_y * TILE_SIZE));
                    scene_particuliere.push_back(a);
                }
                if (event.key.code == Keyboard::B && (niv1.getGlobalBounds().contains(mouseWorldPos))) {
                    Sprite* a = new Sprite;
                    a->setTexture(texture_rouge);
                    Vector2u textureSize = texture_rouge.getSize();
                    a->setScale(static_cast<float>(TILE_SIZE) / textureSize.x,
                        static_cast<float>(TILE_SIZE) / textureSize.y);
                    a->setPosition(centralPane.getPosition() + Vector2f(trig_x * TILE_SIZE, trig_y * TILE_SIZE));
                    scene_particuliere.pop_back();
                    scene_particuliere.push_back(a);
                }
                
                if (event.key.code == Keyboard::B && casewin.getGlobalBounds().contains(mouseWorldPos)) 
                {
                    Sprite* a = new Sprite;
                    a->setTexture(texture_rouge);
                    Vector2u textureSize = texture_rouge.getSize();
                    a->setScale(static_cast<float>(TILE_SIZE) / textureSize.x,
                        static_cast<float>(TILE_SIZE) / textureSize.y);
                    a->setPosition(centralPane.getPosition() + Vector2f(trig_x * TILE_SIZE, trig_y * TILE_SIZE));
                    scene_particuliere.pop_back();
                    scene_particuliere.push_back(a);
                    win= 1;
                }

            }
            if (event.type == Event::MouseButtonPressed
                    && event.mouseButton.button == Mouse::Right
                    && centralPane.getGlobalBounds().contains(mouseWorldPos)) {
                    
                    Sprite* a = new Sprite;
                    a->setTexture(texture_rouge);
                    Vector2u textureSize = texture_rouge.getSize();
                    a->setScale(static_cast<float>(TILE_SIZE) / textureSize.x,
                        static_cast<float>(TILE_SIZE) / textureSize.y);
                    a->setPosition(centralPane.getPosition() + Vector2f(trig_x * TILE_SIZE, trig_y * TILE_SIZE));
                    scene_particuliere.pop_back();
                    


            }
               
            

        }
        

        window.clear();
        window.setView(window.getDefaultView());
        
        // les affichages
        if (win == 0) {
            



            for (Drawable* x : scene_generale) window.draw(*x);
            for (Drawable* x : scene_particuliere) window.draw(*x);
            
        }
        if (win == 1) {

            changertexte(play, "gagne");
            play.setCharacterSize(64);
            window.draw(play);
        }
        
        window.display();
    }

    return EXIT_SUCCESS;
}



void chargertexture() {

    if (!font.loadFromFile("Agatha.ttf")) {
        cout << "erreur" << endl;
    }
}

void changertexte(Text& play, string str) {

    play.setString(str);
    play.setCharacterSize(26);
    play.setFillColor(Color::Magenta);

}*/