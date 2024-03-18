class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])



    def ford_algorithm(self, src,dest):
        dist = [float("Inf")] * self.V
        dist[src] = 0

        for _ in range(self.V - 1):
            for u, v, w in self.graph:
                if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w

        for u, v, w in self.graph:
            if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                print("Graph contains negative weight cycle")
                return

        print(f"Distance from {src} to {dest} : {dist[dest-1]}")


if __name__ == "__main__":
    vertices = int(input("Enter the number of vertices: "))
    graph = Graph(vertices)

    edges = int(input("Enter the number of edges: "))

    print("Enter edges in the format 'source destination weight':")
    for _ in range(edges):
        u, v, w = map(int, input().split())
        graph.add_edge(u, v, w)

    source = int(input("Enter the source vertex: "))
    destination = int(input("Enter the destination vertex: "))

    graph.ford_algorithm(source, destination)
