import pytest

import template_try
from bof3.source.index import Func

TARGET = Func(
    image="exe/slus_004_22",
    name="func_80178764",
    addr=0x80178764,
    size=8,
    words=(1, 2),
    sha1="",
    status="ASM",
    src="src/engine/slus/func_80178764.c",
)
TEMPLATE = Func(
    image="emi/bmagic/magic088/03",
    name="func_801EEC20",
    addr=0x801EEC20,
    size=8,
    words=(1, 2),
    sha1="",
    status="C",
    src="src/overlays/bmagic/magic088/03/BMagic_Effect.c",
)


def test_closest_row_names_the_target_and_its_closest_template(monkeypatch):
    calls = []

    def candidates(_funcs, target, top):
        calls.append((target, top))
        return [(1.0, TEMPLATE)]

    monkeypatch.setattr(template_try.template_diff, "candidates", candidates)
    assert template_try.closest_row(
        [TARGET, TEMPLATE], "exe/slus_004_22@0x80178764"
    ) == ("exe/slus_004_22@func_80178764\temi/bmagic/magic088/03@func_801EEC20")
    assert calls == [(TARGET, 1)]


def test_closest_row_stops_when_nothing_is_lifted(monkeypatch):
    monkeypatch.setattr(template_try.template_diff, "candidates", lambda *_: [])
    with pytest.raises(SystemExit) as stop:
        template_try.closest_row([TARGET], "exe/slus_004_22@0x80178764")
    assert "no lifted function" in str(stop.value.code)
