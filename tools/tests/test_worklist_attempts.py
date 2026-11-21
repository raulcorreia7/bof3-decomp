from worklist import attempts


def test_attempts_keep_each_record(tmp_path):
    path = tmp_path / "attempts.jsonl"
    path.write_text(
        '{"function": "image@0x80000000", "tried": "loop", "first_diff": "load", "score": 90}\n'
        '{"function": "image@0x80000000", "tried": "pointer", "first_diff": "", "score": null}\n'
        '{"function": "other@0x80000000", "tried": "branch", "first_diff": "", "score": null}\n'
        '{"function": "third@0x80000000", "tried": "jump", "first_diff": "size", "score": "46 of 47 instructions"}\n',
        encoding="utf-8",
    )
    assert attempts(path) == {
        "image@0x80000000": "loop; load; 90% | pointer",
        "other@0x80000000": "branch",
        "third@0x80000000": "jump; size; 46 of 47 instructions",
    }
