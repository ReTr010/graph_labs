def bellman_ford_path(matrix, start, end):
    # Преобразование матрицы весов в список рёбер
    edges = []
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j] != -1:
                edges.append((i, j, matrix[i][j]))

    # Инициализация расстояний и предшественников
    distance = [float('inf')] * len(matrix)
    predecessor = [-1] * len(matrix)
    distance[start] = 0

    # Релаксация рёбер
    for _ in range(len(matrix) - 1):
        for u, v, w in edges:
            if distance[u] != float('inf') and distance[u] + w < distance[v]:
                distance[v] = distance[u] + w
                predecessor[v] = u

    # Проверка на циклы отрицательного веса
    for u, v, w in edges:
        if distance[u] != float('inf') and distance[u] + w < distance[v]:
            print("Граф содержит циклы отрицательного веса")
            return None, None

    # Восстановление пути
    path = []
    current_vertex = end
    while current_vertex != start:
        if current_vertex == -1:  # Если путь не найден
            return float('inf'), []
        path.append(current_vertex)
        current_vertex = predecessor[current_vertex]
    path.append(start)
    path.reverse()

    return distance[end], path

# Ввод данных пользователем и вызов функции
vertices = int(input("Введите количество вершин:"))
weights = []
print("Введите матрицу весов:")
for i in range(vertices):
    weights.append(list(map(int, input().split())))


start_vertex = int(input("Введите начальную вершину: "))
end_vertex = int(input("Введите конечную вершину: "))


min_distance, path = bellman_ford_path(weights, start_vertex, end_vertex)
if min_distance is not None:
    print(f"Минимальная стоимость пути от вершины {start_vertex} до вершины {end_vertex} равна {min_distance}")
    print("Путь: " + " -> ".join(map(str, path)))
