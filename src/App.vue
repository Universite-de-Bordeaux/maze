<script setup>
import { ref } from "vue";

const selectedOption = ref("file");
const maze = ref([]);
</script>

<template>
    <div>
        <h1>Maze</h1>
        <div>
            <!-- Selection entre ouvrir un fichier ou générer un labyrinthe -->
            <select v-model="selectedOption">
                <option value="file">Ouvrir un fichier</option>
                <option value="generate">Générer un labyrinthe</option>
            </select>

            <!-- Bouton pour ouvrir un fichier de labyrinthe -->
            <input
                v-if="selectedOption === 'file'"
                type="file"
                @change="openFile"
            />

            <!-- Bouton pour générer un labyrinthe -->
            <button v-if="selectedOption === 'generate'" @click="generateMaze">
                Générer un labyrinthe
            </button>

            <!-- Bouton pour résoudre le labyrinthe -->
            <button v-if="maze.length > 0" @click="solveMaze">
                Résoudre le labyrinthe
            </button>

            <!-- Bouton pour sauvegarder le labyrinthe -->
            <button v-if="maze.length > 0" @click="saveMaze">
                Sauvegarder le labyrinthe
            </button>

            <!-- Bouton pour effacer le labyrinthe -->
            <button v-if="maze.length > 0" @click="clearMaze">
                Effacer le labyrinthe
            </button>

            <!-- Bouton pour afficher le labyrinthe -->
            <button v-if="maze.length > 0" @click="displayMaze">
                Afficher le labyrinthe
            </button>

            <!-- Bouton pour lancer le programme -->
            <button @click="runProgram">Lancer le programme</button>
        </div>
    </div>
</template>

<style scoped>
h1 {
    font-size: 1.5em;
}

div {
    display: flex;
    flex-direction: column;
    align-items: center;
}

input {
    margin: 10px;
}

button {
    margin: 10px;
}
</style>
