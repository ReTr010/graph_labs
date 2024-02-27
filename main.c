#include <stdio.h>
#include <stdlib.h>

// Функция для ввода графа в виде матрицы инцидентности
void inputIncidenceMatrix(int **matrix, int vertices, int edges) {
    printf("Введите матрицу инцидентности (%d x %d):\n", vertices, edges);
    printf("->\n");
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < edges; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Функция для ввода графа в виде матрицы смежности
void inputAdjacencyMatrix(int **matrix, int vertices) {
    printf("Введите матрицу смежности (%d x %d):\n", vertices, vertices);
    printf("->\n");
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Функция для ввода графа в виде списка смежности
int** inputAdjacencyList(int **adjList, int vertices, int edges) {
    printf("Введите смежную вершину для вершины i (или -1 для завершения ввода): \n");
    
    for (int i = 0; i < vertices; ++i) {
        int edges_count = 0;
        printf("Вершина %d:\n", i);
        adjList[i][0] = 0; // Устанавливаем количество смежных вершин для текущей вершины в 0

        for (int j = 1; j <= edges; ++j) {
            if (edges == edges_count){
                break;
            }
            int adjacentVertex;
            printf("->");
            scanf("%d", &adjacentVertex);
            if (adjacentVertex == -1){ // Если введено -1, завершаем ввод для текущей вершины
                break;
            }
            edges_count++;
            adjList[i][0]++; // Увеличиваем количество смежных вершин для текущей вершины
            adjList[i][j] = adjacentVertex; // Записываем смежную вершину в список смежности
        }
    }
    return adjList;
}


// Функция для преобразования из матрицы смежности в список смежности
int** fromAdjacencyMatrixToList(int **adjacencyMatrix, int vertices) {
    int** adjacencyList = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; ++i) {
        int count = 0;
        // Первый проход для подсчета количества смежных вершин
        for (int j = 0; j < vertices; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                count++;
            }
        }
        // Выделяем память для списка смежности, добавляем 1 для хранения количества смежных вершин
        adjacencyList[i] = (int*)malloc((count + 1) * sizeof(int));
        adjacencyList[i][0] = count; // Устанавливаем количество смежных вершин для вершины i
        int k = 1;
        // Второй проход для заполнения списка смежности смежными вершинами
        for (int j = 0; j < vertices; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                adjacencyList[i][k++] = j; // Добавляем смежную вершину
            }
        }
    }
    return adjacencyList;
}


// Функция для преобразования из списка смежности в матрицу смежности
int** fromListToAdjacencyMatrix(int **adjacencyList, int vertices) {
    // Выделяем память под матрицу смежности
    int** adjacencyMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; ++i) {
        // Получаем количество смежных вершин для вершины i
        int count = adjacencyList[i][0];
        // Выделяем память под строку матрицы смежности и инициализируем нулями
        adjacencyMatrix[i] = (int*)calloc(vertices, sizeof(int));
        for (int j = 1; j <= count; ++j) {
            // Заполняем элементы матрицы смежности: если вершина j связана с вершиной i, то ставим 1
            adjacencyMatrix[i][adjacencyList[i][j]] = 1;
        }
    }
    // Возвращаем указатель на созданную матрицу смежности
    return adjacencyMatrix;
}


// Функция для преобразования из матрицы инцидентности в список смежности
int** fromIncidenceMatrixToList(int **incidenceMatrix, int vertices, int edges) {
    int** adjacencyList = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; ++i) {
        int count = 0;
        for (int j = 0; j < edges; ++j) {
            if (incidenceMatrix[i][j] == 1) {
                count++;
            }
        }
        adjacencyList[i] = (int*)malloc((count + 1) * sizeof(int)); // +1 для хранения количества смежных вершин
        adjacencyList[i][0] = count; // Количество смежных вершин для вершины i
        int k = 1;
        for (int j = 0; j < edges; ++j) {
            if (incidenceMatrix[i][j] == 1) {
                for (int m = 0; m < vertices; ++m) {
                    if (incidenceMatrix[m][j] == -1 && m != i) {
                        adjacencyList[i][k++] = m; // Добавляем смежную вершину
                    }
                }
            }
        }
    }
    return adjacencyList;
}


// Функция для преобразования из списка смежности в матрицу инцидентности
int** fromListToIncidenceMatrix(int **adjacencyList, int vertices) {
    // Определение количества рёбер (дуг) в графе
    int edges = 0;
    for (int i = 0; i < vertices; ++i) {
        edges += adjacencyList[i][0];
    }
    edges =  edges/2 + 1; // В неориентированном графе каждое ребро будет учтено дважды
    
    int** incidenceMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; ++i) {
        incidenceMatrix[i] = (int*)calloc(edges, sizeof(int));
    }
    printf("память выделена");
    
    int currentEdge = 0; // Индекс текущего ребра
    for (int i = 0; i < vertices; ++i) {
        for (int j = 1; j <= adjacencyList[i][0]; ++j) {
            int adjVertex = adjacencyList[i][j];
            // Если вершина i меньше, чем смежная вершина adjVertex, это новое ребро
            if (i < adjVertex) {
                // Записываем ребро в матрицу инцидентности
                incidenceMatrix[i][currentEdge] = 1;
                incidenceMatrix[adjVertex][currentEdge] = 1;
                currentEdge++;
            }
        }
    }
    return incidenceMatrix;
}

int** adjacencyList, adjacencyMatrix, incidenceMatrix;




int main() {
    int vertices, edges;
    printf("----------------------------------------------\n");

    printf("В каком виде вы бы хотели ввести матрицу:\n");
    printf("1. Матрица инцидентности\n");
    printf("2. Матрица смежности\n");
    printf("3. Список смежности\n");
    printf("-> ");
    int choise;
    scanf("%d", &choise);
    printf("Введите количество вершин в графе: ");
    scanf("%d", &vertices);
    printf("Введите количество ребер в графе: ");
    scanf("%d", &edges);


    int **incidenceMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; ++i) {
        incidenceMatrix[i] = (int *)malloc(edges * sizeof(int));
    }

    int **adjacencyList = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; ++i) {
        adjacencyList[i] = (int *)malloc(edges * sizeof(int));
    }

    int **adjacencyMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; ++i) {
        adjacencyMatrix[i] = (int *)malloc(vertices * sizeof(int));
    }

    if (choise == 1){

        
        // Выделяем память для матрицы инцидентности
        
        inputIncidenceMatrix(incidenceMatrix, vertices, edges);

        
        adjacencyList = fromIncidenceMatrixToList(incidenceMatrix, vertices, edges);
    }
    if (choise == 2){

 

        inputAdjacencyMatrix(adjacencyMatrix, vertices);
        

        adjacencyList = fromAdjacencyMatrixToList(adjacencyMatrix, vertices);
    }
    if (choise == 3){
        adjacencyList = inputAdjacencyList(adjacencyList, vertices, edges);

    }
    printf("----------------------------------------------\n");
    printf("В каком виде вы бы хотели вывести инофрмацию о графе:\n");
    printf("1. Матрица инцидентности\n");
    printf("2. Матрица смежности\n");
    printf("3. Список смежности\n");
    printf("-> ");
    int choise2;
    scanf("%d", &choise2);
    // Вывод информации о графе в выбранном формате
    // Вывод информации о графе в выбранном формате
switch (choise2) {
    case 1:
        // Преобразование списка смежности в матрицу инцидентности и вывод
        int** incidenceMatrix = fromListToIncidenceMatrix(adjacencyList, vertices);
        // Вывод матрицы инцидентности
        printf("Матрица инцидентности:\n");
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < edges; ++j) {
                printf("%d ", incidenceMatrix[i][j]);
            }
            printf("\n");
        }
        // Освобождение памяти
        for (int i = 0; i < vertices; ++i) {
            free(incidenceMatrix[i]);
        }
        free(incidenceMatrix);
        break;
    case 2:
        // Преобразование списка смежности в матрицу смежности и вывод
        int** adjacencyMatrix = fromListToAdjacencyMatrix(adjacencyList, vertices);
        // Вывод матрицы смежности
        printf("Матрица смежности:\n");
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                printf("%d ", adjacencyMatrix[i][j]);
            }
            printf("\n");
        }
        // Освобождение памяти
        for (int i = 0; i < vertices; ++i) {
            free(adjacencyMatrix[i]);
        }
        free(adjacencyMatrix);
        break;
    case 3:

        // Вывод списка смежности
        printf("Список смежности:\n");
        for (int i = 0; i < vertices; ++i) {
            printf("Вершина %d:", i);
            for (int j = 1; j <=adjacencyList[i][0]; ++j) {
                printf("%d ",adjacencyList[i][j]);
            }
            printf("\n");
        }
        break;
    default:
        printf("Неверный выбор.\n");
}

    return 0;
}

///adad
///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