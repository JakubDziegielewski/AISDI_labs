import pytest
from src.quick_sort import quick_sort
from src.merge_sort import merge_sort
from src.insert_sort import insertion_sort
from src.select_sort import selection_sort
from numpy.random import choice
from numpy.random import seed
import sys


seed(10)
tested_big_array = list(choice(range(-100, 100), 10000, replace=True))
tested_small_array = [11, 14, 88, 90, 30]
tested_string_array = ["ab", "bnv", "aaa", "AX", "a"]
book_contents = [""] * 8000
with open("pan-tadeusz.txt", encoding="utf8") as f:
    book_contents = f.read().split()[:8000]
    
sys.setrecursionlimit(2_000)


def run_tests_for_sorting_method(sorting_method):
    assert sorting_method(tested_small_array) == sorted(tested_small_array)
    assert sorting_method(tested_big_array) == sorted(tested_big_array)
    assert sorting_method(tested_string_array) == sorted(tested_string_array)
    assert sorting_method(book_contents) == sorted(book_contents)


@pytest.mark.timeout(30)
def test_quick_sort():
    run_tests_for_sorting_method(quick_sort)

@pytest.mark.timeout(30)
def test_merge_sort():
    run_tests_for_sorting_method(merge_sort)

@pytest.mark.timeout(30)
def test_insertion_sort():
    run_tests_for_sorting_method(insertion_sort)

@pytest.mark.timeout(30)
def test_selection_sort():
    run_tests_for_sorting_method(selection_sort)
