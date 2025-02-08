#ifndef RAND_HPP
#define RAND_HPP

#include <random>

/**
 * @class Rand
 * @brief Classe permettant de générer des nombres aléatoires
 */
class Rand {
   public:
    /**
     * @brief Constructeur
     */
    Rand();

    /**
     * @brief Génère un nombre aléatoire entre min et max
     * @param min Valeur minimale
     * @param max Valeur maximale
     */
    int get(int min, int max);
    double get(double min, double max);
    bool get(double probability);

    /**
     * @brief Génère un nombre aléatoire
     * @return Nombre aléatoire
     */
    int get();

   private:
    std::mt19937 rng_;  ///< Générateur de nombres aléatoires
};

#endif  // RAND_HPP