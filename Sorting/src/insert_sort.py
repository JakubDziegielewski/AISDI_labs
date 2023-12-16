def insertion_sort(array: list) -> list:
    sorted_ = array.copy()
    for i in range(len(sorted_)):
        while sorted_[i] < sorted_[i - 1] and i > 0:
            sorted_[i], sorted_[i - 1] = sorted_[i - 1], sorted_[i]
            i = i - 1
    return sorted_
