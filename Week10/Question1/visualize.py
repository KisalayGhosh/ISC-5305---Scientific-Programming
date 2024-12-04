import pandas as pd
import matplotlib.pyplot as plt

# Load results
adaptive_results = pd.read_csv('adaptive_results.csv')
nonadaptive_results = pd.read_csv('nonadaptive_results.csv')

# Adaptive: Execution Time vs. Threads
plt.figure(figsize=(8, 6))
plt.plot(adaptive_results['Threads'], adaptive_results['MeanTime'], marker='o', label='Adaptive Mean Time')
plt.fill_between(adaptive_results['Threads'], 
                 adaptive_results['MeanTime'] - adaptive_results['StdDevTime'], 
                 adaptive_results['MeanTime'] + adaptive_results['StdDevTime'], 
                 alpha=0.2, label='Standard Deviation')
plt.xlabel('Threads')
plt.ylabel('Execution Time (s)')
plt.title('Adaptive Method: Execution Time vs. Threads')
plt.legend()
plt.savefig('adaptive_execution_time_vs_threads.png')
plt.show()

# Non-Adaptive: Execution Time vs. Threads
plt.figure(figsize=(8, 6))
plt.plot(nonadaptive_results['Threads'], nonadaptive_results['MeanTime'], marker='o', label='Non-Adaptive Mean Time')
plt.fill_between(nonadaptive_results['Threads'], 
                 nonadaptive_results['MeanTime'] - nonadaptive_results['StdDevTime'], 
                 nonadaptive_results['MeanTime'] + nonadaptive_results['StdDevTime'], 
                 alpha=0.2, label='Standard Deviation')
plt.xlabel('Threads')
plt.ylabel('Execution Time (s)')
plt.title('Non-Adaptive Method: Execution Time vs. Threads')
plt.legend()
plt.savefig('nonadaptive_execution_time_vs_threads.png')
plt.show()

# Adaptive: Mean Evaluations vs. Threads
plt.figure(figsize=(8, 6))
plt.plot(adaptive_results['Threads'], adaptive_results['MeanEvaluations'], marker='o', label='Adaptive Mean Evaluations')
plt.fill_between(adaptive_results['Threads'], 
                 adaptive_results['MeanEvaluations'] - adaptive_results['StdDevEvaluations'], 
                 adaptive_results['MeanEvaluations'] + adaptive_results['StdDevEvaluations'], 
                 alpha=0.2, label='Standard Deviation')
plt.xlabel('Threads')
plt.ylabel('Mean Evaluations')
plt.title('Adaptive Method: Mean Evaluations vs. Threads')
plt.legend()
plt.savefig('adaptive_mean_evaluations_vs_threads.png')
plt.show()

# Non-Adaptive: Mean Evaluations vs. Threads
plt.figure(figsize=(8, 6))
plt.plot(nonadaptive_results['Threads'], nonadaptive_results['MeanEvaluations'], marker='o', label='Non-Adaptive Mean Evaluations')
plt.fill_between(nonadaptive_results['Threads'], 
                 nonadaptive_results['MeanEvaluations'] - nonadaptive_results['StdDevEvaluations'], 
                 nonadaptive_results['MeanEvaluations'] + nonadaptive_results['StdDevEvaluations'], 
                 alpha=0.2, label='Standard Deviation')
plt.xlabel('Threads')
plt.ylabel('Mean Evaluations')
plt.title('Non-Adaptive Method: Mean Evaluations vs. Threads')
plt.legend()
plt.savefig('nonadaptive_mean_evaluations_vs_threads.png')
plt.show()
