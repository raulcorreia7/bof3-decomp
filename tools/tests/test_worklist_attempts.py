import pytest

import worklist
from worklist import attempts


def test_attempts_keep_each_record(tmp_path):
    path = tmp_path / "attempts.tsv"
    path.write_text(
        "function\ttried\tfirst_diff\tscore\n"
        "image@0x80000000\tloop\tload\t90%\n"
        "image@0x80000000\tpointer\t\t\n"
        "other@0x80000000\tbranch\t\t\n"
    )
    assert attempts(path) == {
        "image@0x80000000": "loop; load; 90% | pointer",
        "other@0x80000000": "branch",
    }


def test_templates_names_the_install_step_when_rapidfuzz_is_missing(
    monkeypatch, capsys
):
    def missing(_args):
        raise SystemExit("dups: needs rapidfuzz. Run: tools/setup.sh --matching")

    monkeypatch.setattr(worklist.dups, "main", missing)
    with pytest.raises(SystemExit) as stop:
        worklist.templates()
    assert stop.value.code == 2
    assert "tools/setup.sh --dev --matching" in capsys.readouterr().err
