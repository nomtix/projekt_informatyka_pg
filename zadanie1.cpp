#include <SFML/Graphics.hpp>

int main2()
{
    // 1. Utwórz okno o rozmiarach 800x600 i nadaj mu tytu³
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zadanie 1 - Figury Geometryczne");

    // --- Definiowanie kszta³tów (robimy to PRZED pêtl¹ g³ówn¹) ---

    // 2. Czerwony prostok¹t (budynek)
    sf::RectangleShape prostokat(sf::Vector2f(200.f, 150.f)); // Rozmiar: szerokoœæ 200, wysokoœæ 150
    prostokat.setFillColor(sf::Color::Red);
    prostokat.setPosition(300.f, 400.f); // Pozycja (x, y) lewego górnego rogu
    // Dodajemy obramowanie (zgodnie z zadaniem)
    prostokat.setOutlineThickness(5.f); // Gruboœæ 5 pikseli
    prostokat.setOutlineColor(sf::Color(100, 0, 0)); // Ciemniejszy czerwony

    // 3. Niebieskie ko³o (s³oñce)
    sf::CircleShape kolo(50.f); // Promieñ: 50
    kolo.setFillColor(sf::Color::Blue);
    kolo.setPosition(50.f, 50.f); // Pozycja (x, y) lewego górnego rogu
    // Dodajemy obramowanie
    kolo.setOutlineThickness(3.f); // Gruboœæ 3 pikseli
    kolo.setOutlineColor(sf::Color::Cyan); // Jasnoniebieski

    // 4. Zielony trójk¹t (dach) - u¿ywamy sf::ConvexShape
    sf::ConvexShape trojkat;
    trojkat.setPointCount(3); // Mówimy, ¿e to bêdzie trójk¹t
    // Ustawiamy wspó³rzêdne ka¿dego z 3 wierzcho³ków
    trojkat.setPoint(0, sf::Vector2f(400.f, 300.f));
    trojkat.setPoint(1, sf::Vector2f(500.f, 150.f));
    trojkat.setPoint(2, sf::Vector2f(600.f, 300.f));
    trojkat.setFillColor(sf::Color::Green);
    // Dodajemy obramowanie
    trojkat.setOutlineThickness(4.f); // Gruboœæ 4 pikseli
    trojkat.setOutlineColor(sf::Color(0, 100, 0)); // Ciemnozielony

    // 5. G³ówna pêtla programu (taka sama jak u Ciebie)
    while (window.isOpen())
    {
        // 6. Obs³uga zdarzeñ
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 7. Logika rysowania (w ka¿dej klatce)

        // Czyœcimy okno (dla odmiany na jasnoszary kolor, by figury by³y lepiej widoczne)
        window.clear(sf::Color(200, 200, 200));

        // 8. Rysujemy wszystkie nasze kszta³ty
        window.draw(prostokat);
        window.draw(kolo);
        window.draw(trojkat);

        // 9. Wyœwietlamy gotow¹ klatkê na ekranie
        window.display();
    }

    return 0;
}