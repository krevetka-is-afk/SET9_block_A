import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_theme(style="whitegrid")

df = pd.read_csv("results.csv")

# Время
plt.figure(figsize=(12, 6))
sns.lineplot(data=df, x="Size", y="TimeMs", hue="Algorithm", style="Generator", markers=True)
plt.title("Время выполнения алгоритмов сортировки")
plt.ylabel("Время (мс)")
plt.xlabel("Размер массива")
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.savefig("time_plot.png")
plt.show()

# Сравнения
plt.figure(figsize=(12, 6))
sns.lineplot(data=df, x="Size", y="Comparisons", hue="Algorithm", style="Generator", markers=True)
plt.title("Количество посимвольных сравнений")
plt.ylabel("Сравнения")
plt.xlabel("Размер массива")
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.savefig("comparison_plot.png")
plt.show()