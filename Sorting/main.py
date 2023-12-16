from src.quick_sort import quick_sort
from src.merge_sort import merge_sort
from src.insert_sort import insertion_sort
from src.select_sort import selection_sort
import matplotlib.pyplot as plt
from typing import Callable
from time import process_time
import gc


def measure_average_time(
    sorting_method: Callable,
    words_in_thousands: int,
    number_of_measurements: int
) -> list:
    contents = []
    with open("pan-tadeusz.txt", encoding="utf8") as f:
        contents = f.read().split()
    measured_times = [0] * words_in_thousands
    for _ in range(number_of_measurements):
        for i in range(words_in_thousands):
            table = contents[: (i + 1) * 1000]
            gc_old = gc.isenabled()
            gc.disable()
            start = process_time()
            sorting_method(table)
            end = process_time()
            if gc_old:
                gc.enable()
            measured_times[i] = measured_times[i] + (end - start)
    return [t / number_of_measurements for t in measured_times]


def show_on_plot(function_name: str, average_measured_times: list):
    plt.scatter(
        range(1000, len(average_measured_times) * 1000 + 1, 1000),
        average_measured_times,
    )
    plt.title("Sorting times")
    plt.xlabel("Words sorted")
    plt.ylabel("Number of seconds taken")


def run_experiments(
    sorting_methods: list,
    file_name: str,
    words_in_thousands: int = 10,
    number_of_measurements: int = 1,
):
    for sorting_method in sorting_methods:
        average_measured_times = measure_average_time(
            sorting_method, words_in_thousands, number_of_measurements
        )
        show_on_plot(sorting_method.__name__, average_measured_times)
    plt.legend([x.__name__ for x in sorting_methods])
    plt.savefig(f"{file_name}.png")


def main():
    sorting_methods = [quick_sort, merge_sort, selection_sort, insertion_sort]
    run_experiments(sorting_methods, "Running_time_of_all_methodes")
    plt.clf()
    run_experiments(
        sorting_methods[:2],
        "Average_running_time_of_quick_and_merge_sorts",
        number_of_measurements=200,
    )


if __name__ == "__main__":
    main()
