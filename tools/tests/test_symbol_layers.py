from __future__ import annotations

from bof3.symbols import layers


def test_a_cycle_shares_one_layer() -> None:
    # A <-> B, B -> C, D -> C, E -> E
    edges = [{1}, {0, 2}, set(), {2}, {4}]
    assert layers.assign_layers(5, edges) == [1, 1, 0, 1, 0]
