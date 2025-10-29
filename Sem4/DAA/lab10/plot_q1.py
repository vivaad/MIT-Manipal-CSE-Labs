import matplotlib.pyplot as plt

# Example data (number of vertices vs. operation count)
vertices = [10, 20, 30, 40, 50]
operation_counts = [1000, 8000, 27000, 64000, 125000]

plt.plot(vertices, operation_counts, marker='o')
plt.xlabel('Number of Vertices')
plt.ylabel('Operation Count')
plt.title('Order of Growth for Warshall\'s Algorithm')
plt.show()
