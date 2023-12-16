from random import randrange


def _quick_sort_in_place(collection: list) -> list:
    number_of_elements = len(collection)
    if number_of_elements < 2:
        return collection
    final_pivot_index = _partition(collection)
    return [
        *_quick_sort_in_place(collection[:final_pivot_index]),
        collection[final_pivot_index],
        *_quick_sort_in_place(collection[final_pivot_index + 1 :]),
    ]


def _partition(collection: list):
    number_of_elements = len(collection)
    index_of_pivot = randrange(number_of_elements)
    (collection[0], collection[index_of_pivot]) = (
        collection[index_of_pivot],
        collection[0],
    )
    pivot = collection[0]
    final_pivot_index = 0
    for i in range(1, number_of_elements):
        if collection[i] < pivot:
            (collection[i], collection[final_pivot_index + 1]) = (
                collection[final_pivot_index + 1],
                collection[i],
            )
            final_pivot_index = final_pivot_index + 1
    (collection[0], collection[final_pivot_index]) = (
        collection[final_pivot_index],
        collection[0],
    )
    return final_pivot_index


def quick_sort(collection: list) -> list:
    sorted_collection = collection.copy()
    return _quick_sort_in_place(sorted_collection)
