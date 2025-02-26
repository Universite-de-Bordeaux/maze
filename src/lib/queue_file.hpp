#pragma once
#include <fstream>
#include <string>

#include "rand.hpp"

class QueueFile {
   public:
    /**
     * Constructeur par défaut
     * @param filename Nom du fichier utilisé pour stocker la file
     * @param buffer_size Taille du tampon en mémoire
     */
    explicit QueueFile(std::string filename = "tmp/queue.bin",
                       int buffer_size = 16);
    /**
     * Constructeur de copie
     * @param other Autre instance de QueueFile
     */
    QueueFile(const QueueFile& other);
    /**
     * Destructeur
     */
    ~QueueFile();
    /**
     * Ajoute un élément à la file
     * @param data Pointeur vers les données à ajouter
     */
    void push(void* data);
    /**
     * Retire un élément de la file
     */
    void pop();
    /**
     * Retire un élément aléatoire de la file
     * @param rand Générateur de nombres aléatoires
     * @return Élément retiré
     */
    void* pop(Rand* rand);
    /**
     * Retourne le premier élément de la file
     * @return Premier élément
     */
    void* front() const;
    /**
     * Retourne un élément à partir de l'index spécifié
     * @param index Index de l'élément
     * @return Élément à l'index spécifié
     */
    void* get(int index) const;
    /**
     * Vérifie si la file est vide
     * @return true si la file est vide, false sinon
     */
    bool empty() const;
    /**
     * Retourne la taille de la file
     * @return Taille de la file
     */
    int size() const;

   private:
    std::string filename_;  ///< Nom du fichier
    std::fstream file_;     ///< Fichier utilisé pour stocker les données
    void** buffer_;         ///< Tampon en mémoire
    int buffer_size_;       ///< Taille du tampon
    int buffer_used_;       ///< Nombre d'éléments dans le tampon
    int file_capacity_;     ///< Capacité du fichier
    int file_size_;         ///< Taille actuelle dans le fichier

    /**
     * Synchronise le tampon avec le fichier
     */
    void flush();
    /**
     * Charge le tampon depuis le fichier
     */
    void load();
    /**
     * Redimensionne le tampon
     * @param new_size Nouvelle taille du tampon
     */
    void resize_buffer(int new_size);
};