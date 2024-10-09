import os
import numpy as np
import matplotlib.pyplot as plt

# Create the 'images' directory if it doesn't exist
if not os.path.exists('images'):
    os.makedirs('images')

try:
    # Load vertex areas from file
    vertex_areas = np.loadtxt("vertex_areas.txt")
except OSError:
    print("Error: Unable to open 'vertex_areas.txt'. Please check if the file exists.")
    exit(1)

# Plot histogram of vertex areas
plt.figure()
plt.hist(vertex_areas, bins=50, edgecolor='black')
plt.title('Histogram of Vertex Areas')
plt.xlabel('Area')
plt.ylabel('Frequency')
plt.savefig('images/vertex_areas_histogram.png')
plt.show()

try:
    # Load edge lengths from file
    edge_lengths = np.loadtxt("edge_lengths.txt")
except OSError:
    print("Error: Unable to open 'edge_lengths.txt'. Please check if the file exists.")
    exit(1)

# Plot histogram of edge lengths
plt.figure()
plt.hist(edge_lengths, bins=50, edgecolor='black')
plt.title('Histogram of Edge Lengths')
plt.xlabel('Length')
plt.ylabel('Frequency')
plt.savefig('images/edge_lengths_histogram.png')
plt.show()

# Calculate and print mean and standard deviation of edge lengths
mean_edge_length = np.mean(edge_lengths)
std_edge_length = np.std(edge_lengths)

print(f"Mean edge length: {mean_edge_length:.4f}")
print(f"Standard deviation of edge lengths: {std_edge_length:.4f}")
