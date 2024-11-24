#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "menu/menu.h"
#include "graph/graph.h"
#include "atsp/bruteforce/iterative/bruteforce_iter.h"
#include "atsp/dynamic/dynamic.h"
#include "atsp/bruteforce/optimized/bruteforce_iter_opt.h"
#include "atsp/little/little.h"

int main() {
    menu main_menu(9);

    graph *main_graph = nullptr;

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
        bruteforce_iter_opt bf_iter;
        const auto start_time = std::chrono::high_resolution_clock::now();
        solution sol_2 = bf_iter.solve(*main_graph);
        const auto end_time = std::chrono::high_resolution_clock::now();
        print_solution(sol_2);
        std::cout << "[#] Bruteforce (iteracyjny) - wykonano w "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns"
                  << std::endl;
    });
    main_menu.add_option(4, "Uruchom algorytm B&B (Little)", [&main_graph] {
        if (main_graph == nullptr)
            return;
        little lit;
        const auto start_time = std::chrono::high_resolution_clock::now();
        solution lit_2 = lit.solve(*main_graph);
        const auto end_time = std::chrono::high_resolution_clock::now();
        print_solution(lit_2);
        std::cout << "[#] Branch and Bound (Little) - wykonano w "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns"
                  << std::endl;

    });
    main_menu.add_option(5, "Uruchom algorytm Dynamic Programming (Held-Karp)", [&main_graph] {
        if (main_graph == nullptr)
            return;
        dynamic dyn;
        const auto start_time = std::chrono::high_resolution_clock::now();
        solution dyn_2 = dyn.solve(*main_graph);
        const auto end_time = std::chrono::high_resolution_clock::now();
        print_solution(dyn_2);
        std::cout << "[#] Dynamic Programming (Held-Karp) - wykonano w "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns"
                  << std::endl;

    });
    main_menu.add_option(6, "Obliczenia do sprawozdania", [] {
        static bruteforce_iter_opt bf;
        static little bnb;
        static dynamic dyn;

        static uint16_t bruteforce_sizes[] = {7, 8, 9, 10, 11, 12, 13};
        static uint16_t bnb_sizes[] = {10, 15, 20, 30, 40 ,50, 60};
        static uint16_t dynamic_sizes[] = {16, 17, 18, 19, 20, 21, 22};

        static int repeats = 100;

        std::ofstream output_bf_file("results_bf.txt", std::ios_base::app);

        std::cout << "[#] BRUTEFORCE" << std::endl;
        for (uint16_t size : bruteforce_sizes) {
            output_bf_file << size << ",";
            std::cout << "    [#] Rozmiar: " << size << std::endl;
            long total_ns = 0;
            for (int i = 0; i < repeats; ++i) {
                std::cout << "        [#] Progres: " << i + 1 << "/" << repeats << " (" << ((double) (i + 1) / repeats) * 100 << "%) - ";
                graph to_solve = graph(graph::generate_random_full(size));
                const auto start_time = std::chrono::high_resolution_clock::now();
                solution dyn_2 = bf.solve(to_solve);
                const auto end_time = std::chrono::high_resolution_clock::now();
                auto amount = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                std::cout << amount << "ns" << std::endl;
                total_ns += amount;
            }
            output_bf_file << (total_ns / repeats) << "\n";
        }

        output_bf_file.close();

        std::ofstream output_bnb_file("results_bnb.txt", std::ios_base::app);

        std::cout << "[#] BRANCH AND BOUND" << std::endl;
        for (uint16_t size : bnb_sizes) {
            output_bnb_file << size << ",";
            std::cout << "    [#] Rozmiar: " << size << std::endl;
            long total_ns = 0;
            for (int i = 0; i < repeats; ++i) {
                std::cout << "        [#] Progres: " << i + 1 << "/" << repeats << " (" << ((double) (i + 1) / repeats) * 100 << "%) - ";
                graph to_solve = graph(graph::generate_random_full(size));
                const auto start_time = std::chrono::high_resolution_clock::now();
                solution dyn_2 = bnb.solve(to_solve);
                const auto end_time = std::chrono::high_resolution_clock::now();
                auto amount = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                std::cout << amount << "ns" << std::endl;
                total_ns += amount;
            }
            output_bnb_file << (total_ns / repeats) << "\n";
        }

        output_bnb_file.close();

        std::ofstream output_dp_file("results_dyn.txt", std::ios_base::app);

        std::cout << "[#] DYNAMIC PROGRAMMING" << std::endl;
        for (uint16_t size : dynamic_sizes) {
            output_dp_file << size << ",";
            std::cout << "    [#] Rozmiar: " << size << std::endl;
            long total_ns = 0;
            for (int i = 0; i < repeats; ++i) {
                std::cout << "        [#] Progres: " << i + 1 << "/" << repeats << " (" << ((double) (i + 1) / repeats) * 100 << "%) - ";
                graph to_solve = graph(graph::generate_random_full(size));
                const auto start_time = std::chrono::high_resolution_clock::now();
                solution dyn_2 = dyn.solve(to_solve);
                const auto end_time = std::chrono::high_resolution_clock::now();
                auto amount = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                std::cout << amount << "ns" << std::endl;
                total_ns += amount;
            }
            output_dp_file << (total_ns / repeats) << "\n";
        }

        output_dp_file.close();
    });
    main_menu.add_option(7, "Debug", [&main_graph] {
        static std::random_device r;
        static std::default_random_engine e1(r());
        static std::uniform_int_distribution<int> uniform_dist_weight(7, 16);

        int repeats = 100000;

        little lit;
        dynamic dyn;

        for (int i = 0; i < repeats; i++) {
            graph test_graph(graph::generate_random_full(uniform_dist_weight(e1)));

            std::cout << "[#] TEST " << i + 1 << " z " << repeats << std::endl;
            solution dyn_sol = dyn.solve(test_graph);
            solution lit_sol = lit.solve(test_graph);

            if (dyn_sol.weight == lit_sol.weight) {
                std::cout << "    Pomyślny! " << dyn_sol.weight << " == " << lit_sol.weight << std::endl;
            } else {
                std::cout << "    Zły! " << dyn_sol.weight << " != " << lit_sol.weight << std::endl;
                std::cout << "Graf: " << std::endl;
                test_graph.display();
                std::cout << "Rozwiązanie dyn:" << std::endl;
                print_solution(dyn_sol);
                std::cout << "Rozwiązanie lit:" << std::endl;
                print_solution(lit_sol);
                break;
            }
        }
    });
    main_menu.add_option(8, "Wyjscie", [&main_menu] {
        main_menu.close();
    });

    main_menu.open();

    delete main_graph;
    return 0;
}
