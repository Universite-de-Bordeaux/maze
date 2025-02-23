#include "queue_file.hpp"

#include <algorithm>  // Pour std::copy
#include <iostream>
#include <utility>

QueueFile::QueueFile(std::string filename, const int buffer_size)
    : filename_(std::move(filename)),
      buffer_(new void*[buffer_size]),
      buffer_size_(buffer_size),
      buffer_used_(0),
      file_capacity_(0),
      file_size_(0) {
    // Ouvrir ou créer le fichier
    file_.open(filename_, std::ios::in | std::ios::out | std::ios::binary);
    if (!file_.is_open()) {
        file_.open(filename_, std::ios::out | std::ios::binary);
        if (!file_.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier : " +
                                     filename_);
        }
    }

    // Lire la taille et la capacité du fichier
    if (file_.peek() != std::fstream::traits_type::eof()) {
        file_.read(reinterpret_cast<char*>(&file_capacity_), sizeof(int));
        file_.read(reinterpret_cast<char*>(&file_size_), sizeof(int));
    }

    // Si le fichier est vide, initialiser
    if (file_.tellg() == 0) {
        file_.write(reinterpret_cast<char*>(&file_capacity_), sizeof(int));
        file_.write(reinterpret_cast<char*>(&file_size_), sizeof(int));
    }

    // Charger le tampon
    load();
}

QueueFile::QueueFile(const QueueFile& other)
    : filename_(other.filename_),
      buffer_(new void*[other.buffer_size_]),
      buffer_size_(other.buffer_size_),
      buffer_used_(other.buffer_used_),
      file_capacity_(other.file_capacity_),
      file_size_(other.file_size_) {
    std::copy_n(other.buffer_, other.buffer_used_, buffer_);
}

QueueFile::~QueueFile() {
    // Écrire les modifications dans le fichier
    flush();
    file_.close();
    delete[] buffer_;
}

void QueueFile::load() {
    file_.seekg(2 * sizeof(int));  // Sauter la capacité et la taille
    buffer_used_ = 0;
    // Lire les éléments dans le tampon
    for (int i = 0; i < file_size_; ++i) {
        if (buffer_used_ >= buffer_size_) {
            resize_buffer(buffer_size_ * 2);
        }
        file_.read(static_cast<char*>(buffer_[buffer_used_++]), sizeof(void*));
    }
}

void QueueFile::flush() {
    if (file_size_ != 0) {
        // Écrire les données dans le fichier
        file_.seekp(0);
        file_.write(reinterpret_cast<char*>(&buffer_size_),
                    sizeof(int));  // Écrire la nouvelle capacité
        file_.write(reinterpret_cast<char*>(&file_size_),
                    sizeof(int));  // Écrire la nouvelle taille
        for (int i = 0; i < file_size_; ++i) {
            file_.write(static_cast<char*>(buffer_[i]), sizeof(void*));
        }
    }
}

void QueueFile::resize_buffer(const int new_size) {
    const auto new_buffer = new void*[new_size];
    std::copy_n(buffer_, buffer_used_, new_buffer);
    delete[] buffer_;
    buffer_ = new_buffer;
    buffer_size_ = new_size;
}

void QueueFile::push(void* data) {
    if (buffer_used_ >= buffer_size_) {
        resize_buffer(buffer_size_ * 2);
    }

    buffer_[buffer_used_++] = data;

    file_size_++;
    if (buffer_used_ == buffer_size_) {
        flush();
        load();
    }
}

void QueueFile::pop() {
    if (buffer_used_ == 0) {
        return;
    }

    if (buffer_used_ <= buffer_size_ / 4) {
        resize_buffer(buffer_size_ / 2);
    }

    // Suppression du premier élément du tampon
    auto new_buffer = new void*[buffer_size_ - 1];
    std::copy(buffer_ + 1, buffer_ + buffer_used_, new_buffer);
    delete[] buffer_;
    buffer_ = new_buffer;
    buffer_size_ -= 1;
    buffer_used_--;

    file_size_--;
    flush();
    load();
}

void* QueueFile::pop(Rand* rand) {
    if (buffer_used_ == 0) {
        return nullptr;
    }

    // Sélection aléatoire
    const int index = rand->get(0, buffer_used_ - 1);
    void* result = buffer_[index];

    // Suppression de l'élément sélectionné
    const auto new_buffer = new void*[buffer_size_ - 1];
    std::copy_n(buffer_, index, new_buffer);
    std::copy(buffer_ + index + 1, buffer_ + buffer_used_, new_buffer + index);
    delete[] buffer_;
    buffer_ = new_buffer;
    buffer_size_ -= 1;
    buffer_used_--;

    file_size_--;
    flush();
    load();
    return result;
}

void* QueueFile::front() const {
    if (buffer_used_ == 0) {
        return nullptr;
    }
    return buffer_[0];
}

void* QueueFile::get(const int index) const {
    if (index < 0 || index >= buffer_used_) {
        return nullptr;
    }
    return buffer_[index];
}

bool QueueFile::empty() const { return buffer_used_ == 0; }

int QueueFile::size() const { return file_size_; }