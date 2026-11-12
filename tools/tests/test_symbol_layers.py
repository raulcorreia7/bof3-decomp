from __future__ import annotations

import symbol


def test_a_cycle_shares_one_layer() -> None:
    # A <-> B, B -> C, D -> C, E -> E
    edges = [{1}, {0, 2}, set(), {2}, {4}]
    assert symbol.assign_layers(5, edges) == [1, 1, 0, 1, 0]


def test_a_chain_grows_one_layer_per_call() -> None:
    # 0 -> 1 -> 2 -> 3, and 4 calls 2.
    edges = [{1}, {2}, {3}, set(), {2}]
    assert symbol.assign_layers(5, edges) == [3, 2, 1, 0, 2]


def test_top_level_initializers_keep_their_function_entries() -> None:
    text = (
        "Callback g_Table[3] = {A, (Callback)B, C};\n"
        "void f(void) { Callback local[2] = {B, C}; local[0](); }\n"
    )
    assert dict(symbol._table_initializers(text, {"A", "B", "C"})) == {
        "g_Table": ["A", "B", "C"]
    }
    body = "Callback local[2] = {B, C}; local[0]();"
    assert symbol._local_tables(body, {"A", "B", "C"}) == {"local": ["B", "C"]}


def test_indirect_bases_find_dispatch_and_array_calls() -> None:
    text = (
        "SYS_DISPATCH_BYTE(g_Modes, mode);\n"
        "SYS_DISPATCH_TASK(handlers.steps, 2, task);\n"
        "handlers[step]();\n"
    )
    assert symbol._indirect_bases(text) == {"g_Modes", "handlers"}
