"""The allocation order alloc_priority prints."""

from alloc_priority import allocation_order, priority


def test_priority_truncates_like_gcc():
    assert priority(4, 13) == 6153
    assert priority(3, 10) == 3000
    assert priority(1, 5) == 0


def test_local_blocks_come_first_then_global_by_priority_and_pseudo():
    rows = [
        (74, 3, 10, None),
        (73, 3, 10, None),
        (72, 4, 13, None),
        (90, 3, 4, 2),
        (80, 2, 2, 0),
    ]
    assert [row[0] for row in allocation_order(rows)] == [80, 90, 72, 73, 74]
