def merge_sort(collection: list):
    number_of_elements = len(collection)
    if number_of_elements <= 1:
        return collection
    middle_index = number_of_elements // 2
    first_half = merge_sort(collection[:middle_index])
    second_half = merge_sort(collection[middle_index:])
    return(_merge_two_collections(first_half, second_half))

def _merge_two_collections(first_collection: list, second_collection: list):
    first_len = len(first_collection)
    second_len = len(second_collection)
    first_iterator = 0
    second_iterator = 0
    merged_collection = []
    while first_iterator < first_len and second_iterator < second_len:
        if first_collection[first_iterator] <= second_collection[second_iterator]:
            merged_collection.append(first_collection[first_iterator])
            first_iterator = first_iterator + 1
        else:
            merged_collection.append(second_collection[second_iterator])
            second_iterator = second_iterator + 1
    while first_iterator < first_len:
        merged_collection.append(first_collection[first_iterator])
        first_iterator = first_iterator + 1
    while second_iterator < second_len:
        merged_collection.append(second_collection[second_iterator])
        second_iterator = second_iterator + 1
    return merged_collection
            