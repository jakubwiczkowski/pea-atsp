#include <iostream>
#include <fstream>
#include <chrono>
#include "menu/menu.h"
#include "graph/graph.h"
#include "atsp/bruteforce/iterative/bruteforce_iter.h"
#include "atsp/dynamic/dynamic.h"

int main() {
    menu main_menu(7);

    graph* main_graph = nullptr;

    main_menu.add_option(0, "Wczytanie danych z pliku", [&main_graph] {
        delete main_graph;

        std::cout << "[?] Podaj sciezke do pliku: ";
        std::string path;
        std::cin >> path;
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cout << "[!] Nie udalo sie otworzyc pliku\n";
            return;
        }
        vertex_t vertices = 0;
        file >> vertices;

        main_graph = new graph(vertices);

        for (vertex_t row = 0; row < vertices; ++row) {
            for (vertex_t column = 0; column < vertices; ++column) {
                int weight = 0;
                file >> weight;
                main_graph->set_edge(row, column, weight);
            }
        }
        file.close();
    });
    main_menu.add_option(1, "Wygenerowanie danych losowych", [&main_graph] {
        vertex_t vertices;
        std::cout << "[?] Podaj ilosc miast: ";
        std::cin >> vertices;

        delete main_graph;

        main_graph = new graph(graph::generate_random_full(vertices));
    });
    main_menu.add_option(2, "Wyświetl aktualne dane", [&main_graph] {
        if (main_graph == nullptr) {
            std::cout << "[!] Nie ma zaladowanego grafu!" << std::endl;
            return;
        }

        main_graph->display();
    });
    main_menu.add_option(3, "Uruchom algorytm Bruteforce (iteracyjny)", [&main_graph] {
        if (main_graph == nullptr)
            return;
        bruteforce_iter bf_iter;
        const auto start_time = std::chrono::high_resolution_clock::now();
        solution sol_2 = bf_iter.solve(*main_graph);
        const auto end_time = std::chrono::high_resolution_clock::now();
        print_solution(sol_2);
        std::cout << "[#] Bruteforce (iteracyjny) - wykonano w " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns" << std::endl;
    });
    main_menu.add_option(4, "Uruchom algorytm Dynamic Programming (Held-Karp)", [&main_graph] {
        if (main_graph == nullptr)
            return;
        dynamic dyn;
        const auto start_time = std::chrono::high_resolution_clock::now();
        solution dyn_2 = dyn.solve(*main_graph);
        const auto end_time = std::chrono::high_resolution_clock::now();
        print_solution(dyn_2);
        std::cout << "[#] Dynamic Programming (Held-Karp) - wykonano w " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns" << std::endl;

    });
    main_menu.add_option(5, "Debug", [&main_graph] {
        if (main_graph == nullptr)
            return;

        bruteforce_iter bf_iter;

        solution sol_2 = bf_iter.solve(*main_graph);
        print_solution(sol_2);

        dynamic dyn;

        solution dyn_sol = dyn.solve(*main_graph);
        print_solution(dyn_sol);
    });
    main_menu.add_option(6, "Wyjscie", [&main_menu] {
        main_menu.close();
    });

    main_menu.open();

    delete main_graph;
    return 0;
}
