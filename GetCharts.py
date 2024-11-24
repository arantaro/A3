import matplotlib.pyplot as plt
import csv


def get_cords(filename):
    array_size = []
    quicksort_time = []
    introsort_time = []
    sort_time = []

    with open(filename, "r") as datafile:
        for row in csv.reader(datafile, delimiter=' '):
            array_size.append(float(row[0]))
            quicksort_time.append(float(row[1]))
            introsort_time.append(float(row[2]))
            sort_time.append(float(row[3]))
    return array_size, quicksort_time, introsort_time, sort_time


if __name__ == '__main__':

    for folder_name in ["random_array", "reversed_array", "almost_sorted_array"]:
        plt.plot(1, 1, 1)
        plt.title(folder_name)
        plt.xlabel("Array size")
        plt.ylabel("Microseconds")

        filename = folder_name + "/data.csv"
        array_size, quicksort_time, introsort_time, sort_time = get_cords(filename)
        plt.plot(array_size, quicksort_time, label="QuickSort", color="#1f77b4")
        plt.plot(array_size, introsort_time, label="IntroSort", color="#ff7f0e")
        plt.plot(array_size, sort_time, label="std::sort", color="#2ca02c")

        plt.legend()
        plt.savefig(folder_name + ".png")
        plt.show()
