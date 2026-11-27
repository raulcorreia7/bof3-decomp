"""The strategy order of tools/worklist.py."""

import worklist


def test_strategy_orders_the_lane_and_holds_unit_order_behind_its_culprit(
    monkeypatch, tmp_path
):
    def func(name, addr, words, image="emi/battle/a"):
        return worklist.Func(
            image, name, addr, 4 * len(words), tuple(words), "", "ASM", "x.c"
        )

    body = tuple(range(0x24000001, 0x24000001 + 9))
    funcs = [
        func("culprit", 0x100, (0x24000001,) * 20),
        func("shifted", 0x200, (0x24000002,) * 30),
        func("twin_a", 0x300, body),
        func("twin_b", 0x400, body),
        func("near", 0x500, (0x24000003,) * 40),
        func("other", 0x600, (0x24000004,) * 50, "emi/etc/a"),
    ]
    measures = {
        "culprit": {"kind": "shape", "hunks": 9, "rows": 0, "far": False, "cand": 20},
        "shifted": {"kind": "unit-order", "cand": 30},
        "near": {"kind": "sched", "hunks": 1, "rows": 0, "far": False, "cand": 40},
    }
    monkeypatch.setattr(worklist, "asm_functions", lambda: funcs)
    monkeypatch.setattr(worklist, "is_hand_asm", lambda src: False)
    monkeypatch.setattr(worklist, "is_draft", lambda f: f.name in measures)
    monkeypatch.setattr(worklist, "attempt_notes", lambda: {})
    monkeypatch.setattr(worklist, "measured", lambda f, refresh: measures.get(f.name))
    picks = worklist.strategy(["emi/battle"], [])
    assert [(p.name, p.tier) for p in picks] == [
        ("twin_a", "twin"),
        ("twin_b", "twin"),
        ("near", "near"),
        ("culprit", "medium"),
        ("shifted", "blocked"),
    ]
    assert picks[-1].after == "emi/battle/a@0x00000100"
    assert picks[0].twin == picks[1].twin
    assert worklist.strategy(["emi/battle"], ["near"])[2].name == "culprit"
