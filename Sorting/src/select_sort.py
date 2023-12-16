def selection_sort(array: list) -> list:
    sorted_ = array.copy()
    n = len(sorted_)
    for i in range(n):
        min_ = min(sorted_[i:n])
        j = i + sorted_[i:n].index(min_)
        sorted_[j], sorted_[i] = sorted_[i], sorted_[j]
    return sorted_





