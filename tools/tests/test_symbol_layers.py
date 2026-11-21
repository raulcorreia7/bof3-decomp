from __future__ import annotations

from bof3.symbols import layers


def test_a_cycle_shares_one_layer() -> None:
    # A <-> B, B -> C, D -> C, E -> E
    edges = [{1}, {0, 2}, set(), {2}, {4}]
    assert layers.assign_layers(5, edges) == [1, 1, 0, 1, 0]


def test_a_chain_grows_one_layer_per_call() -> None:
    # 0 -> 1 -> 2 -> 3, and 4 calls 2.
    edges = [{1}, {2}, {3}, set(), {2}]
    assert layers.assign_layers(5, edges) == [3, 2, 1, 0, 2]
